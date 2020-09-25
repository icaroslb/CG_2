#ifndef FACE_H
#define FACE_H

#include "Objeto.h"

template <class T>
class Face : public Objeto<T> {
public:
    Vec_4<T> pos_1;
    Vec_4<T> pos_2;
    Vec_4<T> pos_3;

    Vec_3<T> v_normal;

    Face ( const Vec_4<T> &p_1, const Vec_4<T> &p_2, const Vec_4<T> &p_3, const Vec_3<T> &ambiente, const Vec_3<T> &difusa, const Vec_3<T> &especular, T brilho, T transparencia )
	: Objeto<T>( ambiente, difusa, especular, brilho, transparencia ) 
	, pos_1( p_1 )
	, pos_2( p_2 )
    , pos_3( p_3 )
    {
        v_normal = unitario( produto_vetorial( p_1 - p_3, p_2 - p_3 ) );
    }


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
	bool intersecao ( const Vec_4<T> &origem, const Vec_3<T> &vetor, T &dist, Vec_3<T> &normal, Vec_4<T> &p_colisao )
	{
		const Vec_3<T> vetor_transformado = Objeto<T>::transformacao_mundo_objeto( vetor );
		const Vec_4<T> origem_transfomada = Objeto<T>::transformacao_mundo_objeto( origem );

		const Vec_3<T> vetor_w  = pos_1 - origem_transfomada;

        Vec_3<T> v1p_x_v2p;
        Vec_3<T> v2p_x_v3p;
        Vec_3<T> v3p_x_v1p;

		dist = produto_escalar( vetor_w, v_normal ) / produto_escalar( vetor_transformado, v_normal );
        p_colisao = origem + ( vetor * dist );

        v1p_x_v2p = produto_vetorial( pos_1 - p_colisao, pos_2 - p_colisao );
        v2p_x_v3p = produto_vetorial( pos_2 - p_colisao, pos_3 - p_colisao );
        v3p_x_v1p = produto_vetorial( pos_3 - p_colisao, pos_1 - p_colisao );

        if ( produto_escalar( v1p_x_v2p, v2p_x_v3p ) > 0
        &&   produto_escalar( v3p_x_v1p, v1p_x_v2p ) > 0 ) {
            normal = Objeto<T>::transformacao_objeto_mundo( normal );
            p_colisao = Objeto<T>::transformacao_objeto_mundo( p_colisao );
            
            return true;
        } else {
    		return false;
		}
	}

    /*! normal
    **  Entrada: Ponto referente à normal desejada
    **  Saída:   Vetor normal calculado
    **  Essa função calcula o vetor normal referente ao ponto passado
    **  como parâmetro.
    */
	Vec_3<T> normal( const Vec_4<T> &pos )
	{
        return v_normal;
	}
};

#endif