#ifndef LUZ_CONE_H
#define LUZ_CONE_H

#include "Luz.h"

template <class T>
class Luz_cone : public Luz<T> {
public:
    Vec_3<T> direcao;
    T abertura;
    T decaimento;
    
    /*! Luz_cone
    **  Entrada: Posição, cor, direção e abertura da luz
    **  Saída:
    **  Calcula tanto o ângulo em cosseno e também o fator de decaimento linear
    */
    Luz_cone ( const Vec_3<T> &posicao, const Vec_3<T> &cor, const Vec_3<T> &direcao, T abertura )
    : Luz<T>( posicao, cor )
    , direcao( unitario( direcao ) )
    , abertura( cos( abertura ) )
    , decaimento( T(1) / ( T(1) - this->abertura ) )
    {}

    /*! Calcular_difusa
    **  Entrada: Ponto incidente e normal unitária à face
    **  Saída:   Luz difusa calculada
    **  Essa função calcula a luz difusa de um ponto em relação a uma normal unitária
    */
    Vec_3<T> calcular_difusa ( const Vec_3<T> &ponto, const Vec_3<T> &normal )
    {
        //Calcula o vetor unitário da normal e do ponto à luz
        const Vec_3<T> n = normal;
        const Vec_3<T> l = unitario( Luz<T>::posicao - ponto );

        const Vec_3<T> vetor_ponto = unitario( ponto - Luz<T>::posicao );
        const T angulo_calc = produto_escalar( direcao, vetor_ponto );

        if ( produto_escalar( n, l ) >= T(0) && angulo_calc > abertura )
            return Luz<T>::cor
                 * ( ( angulo_calc - abertura ) * decaimento )
                 * produto_escalar( n, l );
        else
            return Vec_3<T>();
        
    }

    /*! Calcular_especular
    **  Entrada: Ponto incidente, normal unitária à face, posição do observador, e o fator do brilho do material
    **  Saída:   Luz especular calculada
    **  Essa função calcula a luz especular de um ponto em relação a uma normal unitária
    **  e a posição do observador.
    */
    Vec_3<T> calcular_especular ( const Vec_3<T> &ponto, const Vec_3<T> &normal, const Vec_3<T> &origem, T brilho )
    {
         //Calcula o vetor unitário da normal, o vetor apontando para o observador e do ponto à luz
        const Vec_3<T> n = normal;
        const Vec_3<T> v = unitario( origem - ponto );
        const Vec_3<T> l = unitario( ponto - Luz<T>::posicao );
        //Projeta o vetor da luz no vetor normal, inverte e usa-o para espelhar o vetor da luz
        const Vec_3<T> l_proj = -projecao_unitario( l, n );
        const Vec_3<T> l_l = l + ( T(2) * l_proj );

        const Vec_3<T> vetor_ponto = unitario( ponto - Luz<T>::posicao );
        const T angulo_calc = produto_escalar( direcao, vetor_ponto );


        //Se a luz não estiver atrás da face e o observador estiver recebendo alguma contribuição
        //da especular, calcula.
        if ( produto_escalar( n, l ) <= T(0) && produto_escalar( v, l_l ) >= T(0) && angulo_calc > abertura )
            return Luz<T>::cor * ( ( angulo_calc - abertura ) * decaimento ) * T( pow( produto_escalar( v, l_l ), brilho ) );
        else
            return Vec_3<T>();
    }

};

#endif