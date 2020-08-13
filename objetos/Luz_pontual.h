#ifndef LUZ_PONTUAL_H
#define LUZ_PONTUAL_H

#include "Luz.h"

template <class T>
class Luz_pontual : public Luz<T> {
public:
    Luz_pontual ( const Vec_3<T> &posicao, const Vec_3<T> &cor )
    : Luz<T>( posicao, cor )
    {}

    Vec_3<T> calcular_difusa ( const Vec_3<T> &ponto, const Vec_3<T> &normal )
    {
        const Vec_3<T> n = unitario( normal );
        const Vec_3<T> l = unitario( Luz<T>::posicao - ponto );

        if ( produto_escalar( n, l ) >= T(0) )
            return Luz<T>::cor * produto_escalar( n, l );
        else
            return Vec_3<T>();
        
    }

    Vec_3<T> calcular_especular ( const Vec_3<T> &ponto, const Vec_3<T> &normal, const Vec_3<T> &origem, T brilho )
    {
        const Vec_3<T> n = unitario( normal );
        const Vec_3<T> v = unitario( origem - ponto );
        const Vec_3<T> l = unitario( ponto - Luz<T>::posicao );
        const Vec_3<T> m_l = projecao_unitario( l, n );
        const Vec_3<T> l_l = l - ( T(2) * m_l );


        if ( produto_escalar( n, l ) <= T(0) )
            return Luz<T>::cor * T( pow( produto_escalar( v, l_l ), brilho ) );
        else
            return Vec_3<T>();
    }

};

#endif