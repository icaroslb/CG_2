#ifndef LUZ_PONTUAL_H
#define LUZ_PONTUAL_H

#include "Luz.h"

template <class T>
class Luz_pontual : public Luz<T> {
public:
    /*! Luz_pontual
    **  Entrada: Posição e a cor da luz
    **  Saída:
    */
    Luz_pontual ( const Vec_3<T> &posicao, const Vec_3<T> &cor )
    : Luz<T>( posicao, cor )
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

        if ( produto_escalar( n, l ) >= T(0) )
            return Luz<T>::cor * produto_escalar( n, l );
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

        //Se a luz não estiver atrás da face e o observador estiver recebendo alguma contribuição
        //da especular, calcula.
        if ( produto_escalar( n, l ) <= T(0) && produto_escalar( v, l_l ) >= T(0) )
            return Luz<T>::cor * T( pow( produto_escalar( v, l_l ), brilho ) );
        else
            return Vec_3<T>();
    }

};

#endif