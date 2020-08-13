#ifndef OPERACOES_H
#define OPERACOES_H

#include "Matriz_4.h"

template <class T> Matriz_4<T> transladar ( const Matriz_4<T> &M, T x, T y, T z );
template <class T> Matriz_4<T> escalar ( const Matriz_4<T> &M, T x, T y, T z );
template <class T> Matriz_4<T> rotacionar ( const Matriz_4<T> &M, T x, T y, T z );

#endif
