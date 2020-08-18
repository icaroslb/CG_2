#ifndef ESFERA_H
#define ESFERA_H

#include "Objeto.h"

template< class T >
class Esfera : public Objeto<T> {
public:
	Vec_4<T> posicao;
	T raio;
	
	/*! Objeto
    **  Entrada: A posição e o raio da esfera e os valores de ambiente, difusa,
	**  especular e o fator do brilho do material
    **  Saída:
    */
	Esfera( const Vec_4<T> &posicao, T raio, const Vec_3<T> &ambiente, const Vec_3<T> &difusa, const Vec_3<T> &especular, T brilho )
	: Objeto<T>( ambiente, difusa, especular, brilho ) 
	, posicao( posicao )
	, raio( raio )
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
	bool intersecao ( const Vec_4<T> &origem, const Vec_3<T> &vetor, T &dist, Vec_3<T> &normal, Vec_4<T> &p_colisao )
	{
		const Vec_3<T> raio_transformado = Objeto<T>::transformacao_mundo_objeto( vetor );
		const Vec_4<T> origem_transfomada = Objeto<T>::transformacao_mundo_objeto( origem );
		const Vec_3<T> v_posicao = origem_transfomada - posicao;

		const T alfa  = produto_escalar( raio_transformado, raio_transformado );
		const T beta  = T(2) * produto_escalar( raio_transformado, v_posicao );
		const T gamma = produto_escalar( v_posicao, v_posicao ) - ( raio * raio );

		const T delta = ( beta * beta ) - ( T(4) * alfa * gamma );

		T t1;
		T t2;

		if ( delta < T(0) ) {
			dist = std::numeric_limits<T>::infinity();
			return false;
		} else {

			if ( delta == T(0) ) {
				dist = t1 = t2 = ( -beta + sqrt( delta ) ) / ( T(2) * alfa );
			} else {
				t1 = ( -beta + sqrt( delta ) ) / ( T(2) * alfa );
				t2 = ( -beta - sqrt( delta ) ) / ( T(2) * alfa );

				dist = ( ( t1 < t2 && t1 >= T(0) ) ? t1 : t2 );
			}

			normal = Objeto<T>::transformacao_objeto_mundo( this->normal( ( origem_transfomada + ( raio_transformado * dist ) ) ) );
			//p_colisao = Objeto<T>::transformacao_objeto_mundo( origem_transfomada + ( raio_transformado * dist ) );
			p_colisao = Objeto<T>::transformacao_objeto_mundo( origem_transfomada + ( raio_transformado * dist ) );

			return true;

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
		return unitario( pos - posicao );
	}

};

#endif
