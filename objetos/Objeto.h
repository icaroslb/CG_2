#ifndef OBJETO_H
#define OBJETO_H

#include "../Algebra/include_algebra.h"

template <class T>
class Retorno {
    T distancia;
    Vec_3<T> normal;
};

template <class T>
class Objeto {
public:
    Matriz_4<T> matriz_tranformacao;

    Vec_3<T> ambiente;
    Vec_3<T> difusa;
    Vec_3<T> especular;
    T brilho;

    Objeto( const Vec_3<T> &ambiente, const Vec_3<T> &difusa, const Vec_3<T> &especular, T brilho )
    : matriz_tranformacao(Matriz_tipo::IDENTIDADE)
    , ambiente( ambiente )
    , difusa( difusa )
    , especular( especular )
    , brilho( brilho )
    {}

    virtual bool intersecao ( const Vec_3<T> &origem, const Vec_3<T> &vetor, T &dist, Vec_3<T> &normal ) = 0;
    virtual Vec_3<T> normal( const Vec_3<T> &pos ) = 0;
};

#endif