#ifndef LUZ_H
#define LUZ_H

#include "../Algebra/include_algebra.h"

template <class T>
class Luz {
public:
    Vec_4<T> posicao;
    Vec_3<T> cor;

    /*! Luz
    **  Entrada: Posição e a cor da luz
    **  Saída:
    */
    Luz ( const Vec_4<T> &posicao, const Vec_3<T> &cor )
    : posicao( posicao )
    , cor( cor )
    {}

    /*! Calcular_difusa
    **  Entrada: Ponto incidente e normal unitária à face
    **  Saída:   Luz difusa calculada
    **  Essa função calcula a luz difusa de um ponto em relação a uma normal unitária
    */
    virtual Vec_3<T> calcular_difusa ( const Vec_4<T> &ponto, const Vec_3<T> &normal ) = 0;
    
    /*! Calcular_especular
    **  Entrada: Ponto incidente, normal unitária à face, posição do observador, e o valor do brilho do material
    **  Saída:   Luz especular calculada
    **  Essa função calcula a luz especular de um ponto em relação a uma normal unitária
    **  e a posição do observador.
    */
    virtual Vec_3<T> calcular_especular ( const Vec_4<T> &ponto, const Vec_3<T> &normal, const Vec_4<T> &origem, T brilho ) = 0;
};

#endif