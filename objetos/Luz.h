#ifndef LUZ_H
#define LUZ_H

#include "../Algebra/include_algebra.h"

template <class T>
class Luz {
public:
    Vec_3<T> posicao;
    Vec_3<T> cor;

    Luz ( const Vec_3<T> &posicao, const Vec_3<T> &cor )
    : posicao( posicao )
    , cor( cor )
    {}

    virtual Vec_3<T> calcular_difusa ( const Vec_3<T> &ponto, const Vec_3<T> &normal ) = 0;
    virtual Vec_3<T> calcular_especular ( const Vec_3<T> &ponto, const Vec_3<T> &normal, const Vec_3<T> &origem, T brilho ) = 0;
};

#endif