#ifndef MUNDO_H
#define MUNDO_H

#include <vector>
#include <limits>
#include <random>
#include "Objeto.h"
#include "Luz.h"

template <class T>
class Mundo {
public:
    std::vector<Objeto<T>*> objetos;
    std::vector<Luz<T>*> luzes;

    /*! Mundo
    **  Entrada:
    **  Saída:
    */
    Mundo () {}

    /*! calcular_cor
    **  Entrada: Posição do observador, vetor direção e um valor de erro
    **  Saída:   A cor calculada referênte ao raio
    **  Essa função calcula a cor referênte a interseção de menor valor não negativo
    **  e a interação das luzes com o material naquele ponto. O valor do erro é utilizado
    **  para que não haja problemas do raio ficar preso na cena.
    */
    Vec_3<T> calcular_cor ( const Vec_4<T> &origem, const Vec_3<T> &vetor, T erro = T(0.01) )
    {
        bool intersecao = false;
        bool ocorreu_intersecao = false;

        T menor_dist = std::numeric_limits<T>::infinity();
        T aux_dist;

        size_t menor_dist_id;
        size_t aux_id = 0;
        Vec_3<T> aux_normal;
        Vec_3<T> menor_normal;

        Vec_4<T> pos_aux;
        Vec_4<T> pos;
        Vec_3<T> normal;
        Vec_3<T> v_luz;
        Vec_3<T> difusa_calc;
        Vec_3<T> epecular_calc;

        // procura se há alguma interseção válida
        for ( auto o : objetos ) {
            intersecao = false;
            intersecao = o->intersecao( origem, vetor, aux_dist, aux_normal, pos_aux );

            if ( intersecao && menor_dist > aux_dist && aux_dist > erro ) {
                ocorreu_intersecao = true;
                menor_dist = aux_dist;
                menor_dist_id = aux_id;
                menor_normal = aux_normal;
                pos = pos_aux;
            }

            aux_id++;
        }

        if ( ocorreu_intersecao ) {
            normal = unitario( menor_normal );
            
            //Calcula a iteração de cada luz com o ponto achado
            for ( auto l : luzes ) {
                v_luz = unitario( l->posicao - pos );
                intersecao = false;
                aux_dist = T(0);

                //Verifica se há algum objeto entre o ponto e a luz analizada
                for ( auto o : objetos ) {
                    intersecao = o->intersecao( pos, v_luz, aux_dist, aux_normal, pos_aux );

                    if ( intersecao && aux_dist > erro ) {
                        break;
                    } else {
                        intersecao = false;
                    }
                }

                //Calcula a iteração da luz analizada com o material, caso não haja nenhum
                //objeto entre o ponto e a luz
                if ( !intersecao ) {
                    difusa_calc += objetos[menor_dist_id]->difusa * l->calcular_difusa( pos, normal );
                    epecular_calc += objetos[menor_dist_id]->especular * l->calcular_especular( pos, normal, origem, objetos[menor_dist_id]->brilho );
                }
            }

            return ( Vec_3f( 0.7f, 0.7f, 0.7f ) * objetos[menor_dist_id]->ambiente )
                   + difusa_calc
                   + epecular_calc;
        } else {
            return Vec_3<T>();
        }
    }


    Vec_3<T> calcular_cor_recusivo ( const Vec_4<T> &origem, const Vec_3<T> &vetor, T erro = T(0.01), int max_r = 0, int rec = 0 )
    {
        bool intersecao = false;
        bool ocorreu_intersecao = false;

        T menor_dist = std::numeric_limits<T>::infinity();
        T aux_dist;

        size_t menor_dist_id;
        size_t aux_id = 0;
        Vec_3<T> aux_normal;
        Vec_3<T> menor_normal;

        Vec_4<T> pos_aux;
        Vec_4<T> pos;
        Vec_3<T> normal;
        Vec_3<T> v_luz;
        Vec_3<T> ambiente_calc;
        Vec_3<T> difusa_calc;
        Vec_3<T> epecular_calc;

        Vec_3<T> cor_calculada;
        Vec_3<T> cor_recursiva_reflexao;
        Vec_3<T> cor_recursiva_refracao;

        Vec_3<T> vetor_refletido;
        Vec_3<T> vetor_refracionado;
        
        // procura se há alguma interseção válida
        for ( auto o : objetos ) {
            intersecao = false;
            intersecao = o->intersecao( origem, vetor, aux_dist, aux_normal, pos_aux );

            if ( intersecao && menor_dist > aux_dist && aux_dist >= T(0) && fabs( aux_dist ) > erro ) {
                ocorreu_intersecao = true;
                menor_dist = aux_dist;
                menor_dist_id = aux_id;
                menor_normal = aux_normal;
                pos = pos_aux;
            }

            aux_id++;
        }

        if ( ocorreu_intersecao ) {
            normal = unitario( menor_normal );
            
            //Calcula a iteração de cada luz com o ponto achado
            for ( auto l : luzes ) {
                v_luz = unitario( l->posicao - pos );
                intersecao = false;
                aux_dist = T(0);

                //Verifica se há algum objeto entre o ponto e a luz analizada
                for ( auto o : objetos ) {
                    intersecao = o->intersecao( pos, v_luz, aux_dist, aux_normal, pos_aux );

                    if ( intersecao && aux_dist >= T(0) && aux_dist > erro ) {
                        break;
                    } else {
                        intersecao = false;
                    }
                }

                //Calcula a iteração da luz analizada com o material, caso não haja nenhum
                //objeto entre o ponto e a luz
                if ( !intersecao ) {
                    difusa_calc += objetos[menor_dist_id]->difusa * l->calcular_difusa( pos, normal );
                    epecular_calc += objetos[menor_dist_id]->especular * l->calcular_especular( pos, normal, origem, objetos[menor_dist_id]->brilho );
                }
            }

            ambiente_calc = Vec_3f( 0.7f, 0.7f, 0.7f ) * objetos[menor_dist_id]->ambiente;

            cor_calculada = ambiente_calc
                          + difusa_calc
                          + epecular_calc;
            
            if ( rec < 5 ) {
                vetor_refletido = vetor_reflexao( vetor, normal );
                vetor_refracionado = vetor_refracao( vetor, normal, T(1), T(1) );

                cor_recursiva_reflexao = objetos[menor_dist_id]->difusa
                                       * calcular_cor_recusivo( pos, vetor_refletido, erro, max_r, rec + 1 );
                
                if ( objetos[menor_dist_id]->transparencia > erro ) {
                    cor_recursiva_refracao = objetos[menor_dist_id]->transparencia
                                           * calcular_cor_recusivo( pos, vetor_refracionado, erro, max_r, rec + 1 );
                    cor_calculada *= T(1) - objetos[menor_dist_id]->transparencia;
                }
            }

        }

        return cor_calculada + cor_recursiva_reflexao + cor_recursiva_refracao;
    }

    Vec_3<T> calcular_cor_recusivo_sample ( const Vec_4<T> &origem, T x_min, T x_max, T y_min, T y_max, T z, T erro = T(0.01), int qtd_sample = 1, int max_r = 0, int rec = 0 )
    {

        Vec_3<T> cor_calculada;
        Vec_3<T> vetor;
        static std::random_device r_d;

        T dif_x = x_max - x_min;
        T dif_y = y_max - y_min;

        T random_x;
        T random_y;

        //int qtd_sample_2 = qtd_sample * qtd_sample;

        for ( int i = 0; i < qtd_sample; i++ ) {
            random_x = T(r_d()) / T(r_d.max());
            random_y = T(r_d()) / T(r_d.max());
            
            vetor._x = ( random_x * dif_x ) + x_min;
            vetor._y = ( random_y * dif_x ) + y_min;
            vetor._z = z;

            vetor = unitario( vetor );
            
            cor_calculada += calcular_cor_recusivo( origem, vetor, erro, max_r, rec );
        }

        if ( qtd_sample > 1 )
            cor_calculada /= T(qtd_sample);

        return cor_calculada;

    }

};

#endif