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
    Matriz_4<T> matriz_tranformacao_inversa;

    Vec_3<T> ambiente;
    Vec_3<T> difusa;
    Vec_3<T> especular;
    T brilho;

    /*! Objeto
    **  Entrada: Os valores de ambiente, difusa, especular e o fator do brilho do material
    **  Saída:
    */
    Objeto( const Vec_3<T> &ambiente, const Vec_3<T> &difusa, const Vec_3<T> &especular, T brilho )
    : matriz_tranformacao( Matriz_tipo::IDENTIDADE )
    , matriz_tranformacao_inversa( Matriz_tipo::IDENTIDADE )
    , ambiente( ambiente )
    , difusa( difusa )
    , especular( especular )
    , brilho( brilho )
    {}

    /*! intersecao
    **  Entrada: Ponto do observador, vetor direção, distância que será calculada
    **           e a normal que será calculada
    **  Saída:   Se houver interseção entre o raio e o objeto, a distância calculada
    **           e a normal calculada
    **  Essa função verifica se há interseção entre o raio e o objeto. Pelo parâmetro dist,
    **  retorna a menor não negativa interseção caso haja múltiplas com pelo menos uma positiva,
    **  caso não haja retornará uma das posibilidades. Pelo parâmetro normal, retorna o valor do
    **  vetor normal à interseção referênte a distância retornada.
    */
    virtual bool intersecao ( const Vec_3<T> &origem, const Vec_3<T> &vetor, T &dist, Vec_3<T> &normal ) = 0;
    
    /*! normal
    **  Entrada: Ponto referente à normal desejada
    **  Saída:   Vetor normal calculado
    **  Essa função calcula o vetor normal referente ao ponto passado
    **  como parâmetro.
    */
    virtual Vec_3<T> normal( const Vec_3<T> &pos ) = 0;

    Vec_3<T> transformacao_mundo_objeto ( const Vec_3<T> &v )
    {
        return matriz_tranformacao_inversa * v;
    }

    Vec_3<T> transformacao_objeto_mundo ( const Vec_3<T> &v )
    {
        return transposta( matriz_tranformacao_inversa ) * v;
    }
};

#endif