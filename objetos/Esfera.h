#ifndef ESFERA_H
#define ESFERA_H

#include "Objeto.h"

template< class T >
class Esfera : public Objeto<T> {
public:
	Vec_3<T> posicao;
	Vec_3<T> cor;
	T raio;
		
	Esfera( const Vec_3<T> &posicao, T raio, const Vec_3<T> &ambiente, const Vec_3<T> &difusa, const Vec_3<T> &especular, T brilho )
	: Objeto<T>( ambiente, difusa, especular, brilho ) 
	, posicao( posicao )
	, raio( raio )
	{}
	
	bool intersecao ( const Vec_3<T> &origem, const Vec_3<T> &vetor, T &dist )
	{
		const Vec_3<T> v_posicao = origem - posicao;

		const T alfa  = produto_escalar( vetor, vetor );
		const T beta  = T(2) * produto_escalar( vetor, v_posicao );
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

				dist = ( ( t1 < t2 ) ? t1 : t2 );
			}

			//std::cout << __FILE__ << " - " << dist << " - " << t1 << " - " << t2 << std::endl;

			return true;

		}
	}

	Vec_3<T> normal( const Vec_3<T> &pos )
	{
		return unitario( pos - posicao );
	}

};

#endif
