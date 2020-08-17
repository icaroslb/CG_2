#ifndef MUNDO_H
#define MUNDO_H

#include <vector>
#include <limits>
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
    Vec_3<T> calcular_cor ( const Vec_3<T> &origem, const Vec_3<T> &vetor, T erro = T(0.01) )
    {
        bool intersecao = false;
        bool ocorreu_intersecao = false;

        T menor_dist = std::numeric_limits<T>::infinity();
        T aux_dist;

        size_t menor_dist_id;
        size_t aux_id = 0;
        Vec_3<T> aux_normal;
        Vec_3<T> menor_normal;

        Vec_3<T> pos;
        Vec_3<T> normal;
        Vec_3<T> v_luz;
        Vec_3<T> difusa_calc;
        Vec_3<T> epecular_calc;

        // procura se há alguma interseção válida
        for ( auto o : objetos ) {
            intersecao = false;
            intersecao = o->intersecao( origem, vetor, aux_dist, aux_normal );

            if ( intersecao && menor_dist > aux_dist && aux_dist > erro ) {
                ocorreu_intersecao = true;
                menor_dist = aux_dist;
                menor_dist_id = aux_id;
                menor_normal = aux_normal;
            }

            aux_id++;
        }

        if ( ocorreu_intersecao ) {
            pos = origem + ( vetor * menor_dist );
            normal = unitario( menor_normal );
            
            //Calcula a iteração de cada luz com o ponto achado
            for ( auto l : luzes ) {
                v_luz = unitario( l->posicao - pos );
                intersecao = false;
                aux_dist = T(0);

                //Verifica se há algum objeto entre o ponto e a luz analizada
                for ( auto o : objetos ) {
                    intersecao = o->intersecao( pos, v_luz, aux_dist, aux_normal );

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
};

#endif