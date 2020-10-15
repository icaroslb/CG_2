#ifndef OPERACOES_H
#define OPERACOES_H

#include "Matriz_4.h"

template <class T>
Matriz_4<T> transladar ( T x, T y, T z )
{
    Matriz_4<T> m( Matriz_tipo::IDENTIDADE );

    m( 0, 3 ) = x;
    m( 1, 3 ) = y;
    m( 2, 3 ) = z;

    return m;
}

template <class T>
Matriz_4<T> escalar ( T x, T y, T z )
{
    Matriz_4<T> m( Matriz_tipo::IDENTIDADE );

    m( 0, 0 ) = x;
    m( 1, 1 ) = y;
    m( 2, 2 ) = z;

    return m;
}

template <class T>
Matriz_4<T> rotacionar ( Ori_transf tipo, T ang )
{
    Matriz_4<T> m( Matriz_tipo::IDENTIDADE );
    
    switch ( tipo )
    {
    case Ori_transf::xy:
        m( 0, 0 ) =  cos( ang ); m( 0, 1 ) = -sin( ang );
        m( 1, 0 ) =  sin( ang ); m( 1, 1 ) =  cos( ang );
    break;
    case Ori_transf::yz:
        m( 1, 1 ) =  cos( ang ); m( 1, 2 ) = -sin( ang );
        m( 2, 1 ) =  sin( ang ); m( 2, 2 ) =  cos( ang );
    break;
    case Ori_transf::zx:
        m( 0, 0 ) =  cos( ang ); m( 0, 2 ) =  sin( ang );
        m( 2, 0 ) = -sin( ang ); m( 2, 2 ) =  cos( ang );
    break;
    }

    return m;
}

template <class T>
Matriz_4<T> inversa_TRS ( T s_x, T s_y, T s_z
                        , Ori_transf tipo, T ang
                        , T t_x, T t_y, T t_z )
{
    Matriz_4<T> I( Matriz_tipo::IDENTIDADE );
    Matriz_4<T> R = rotacionar( tipo, ang );

    Vec_3<T> r_x = Vec_3<T>( R( 0, 0 ), R( 1, 0 ), R( 2, 0 ) );
    Vec_3<T> r_y = Vec_3<T>( R( 0, 1 ), R( 1, 1 ), R( 2, 1 ) );
    Vec_3<T> r_z = Vec_3<T>( R( 0, 2 ), R( 1, 2 ), R( 2, 2 ) );

    Vec_3<T> i_r_x = Vec_3<T>( R( 0, 0 ), R( 1, 0 ), R( 2, 0 ) ) / s_x;
    Vec_3<T> i_r_y = Vec_3<T>( R( 0, 1 ), R( 1, 1 ), R( 2, 1 ) ) / s_y;
    Vec_3<T> i_r_z = Vec_3<T>( R( 0, 2 ), R( 1, 2 ), R( 2, 2 ) ) / s_z;

    Vec_3<T> t = Vec_3<T>( t_x, t_y, t_z );

    I( 0, 0 ) = i_r_x._x;
    I( 0, 1 ) = i_r_x._y;
    I( 0, 2 ) = i_r_x._z;
    I( 0, 3 ) = - ( produto_escalar( r_x, t ) / s_x );

    I( 1, 0 ) = i_r_y._x;
    I( 1, 1 ) = i_r_y._y;
    I( 1, 2 ) = i_r_y._z;
    I( 1, 3 ) = - ( produto_escalar( r_y, t ) / s_y );

    I( 2, 0 ) = i_r_z._x;
    I( 2, 1 ) = i_r_z._y;
    I( 2, 2 ) = i_r_z._z;
    I( 2, 3 ) = - ( produto_escalar( r_z, t ) / s_z );

    return I;
}

#endif
