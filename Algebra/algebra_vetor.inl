template <class T>
T produto_escalar ( const Vec_2<T> &v1, const Vec_2<T> &v2 )
{
	return ( v1._x * v2._x ) + ( v1._y * v2._y );
}
/*===============================================================================================================================*/
template <class T>
T produto_escalar ( const Vec_3<T> &v1, const Vec_3<T> &v2 )
{
	return ( v1._x * v2._x ) + ( v1._y * v2._y ) + ( v1._z * v2._z );
}
/*===============================================================================================================================*/
template <class T>
T produto_escalar ( const Vec_4<T> &v1, const Vec_4<T> &v2 )
{
	return ( v1._x * v2._x ) + ( v1._y * v2._y ) + ( v1._z * v2._z ) + ( v1._w * v2._w );
}
/*===============================================================================================================================*/
template <class T>
T produto_vetorial ( const Vec_2<T> &v1, const Vec_2<T> &v2 )
{
	return ( v1._x * v2._y ) - ( v1._y * v2._x );
}
/*===============================================================================================================================*/
template <class T>
Vec_3<T> produto_vetorial ( const Vec_3<T> &v1, const Vec_3<T> &v2 )
{
	return Vec_3<T>( ( v1._y * v2._z ) - ( v1._z * v2._y ),
	                 ( v1._z * v2._x ) - ( v1._x * v2._z ),
	                 ( v1._x * v2._y ) - ( v1._y * v2._x ) );
}
/*===============================================================================================================================*/
template <class T>
Vec_4<T> produto_vetorial ( const Vec_4<T> &v1, const Vec_4<T> &v2 )
{
	return Vec_4<T>( ( v1._y * v2._z ) - ( v1._z * v2._y ),
	                 ( v1._z * v2._x ) - ( v1._x * v2._z ),
	                 ( v1._x * v2._y ) - ( v1._y * v2._x ),
	                 0 );
}
/*===============================================================================================================================*/
template <class T>
T norma_quadrada ( const Vec_2<T> &v )
{
	return ( v._x * v._x ) + ( v._y * v._y );
}
/*===============================================================================================================================*/
template <class T>
T norma_quadrada ( const Vec_3<T> &v )
{
	return ( v._x * v._x ) + ( v._y * v._y ) + ( v._z * v._z );
}
/*===============================================================================================================================*/
template <class T>
T norma_quadrada ( const Vec_4<T> &v )
{
	return ( v._x * v._x ) + ( v._y * v._y ) + ( v._z * v._z ) + ( v._w * v._w );
}
/*===============================================================================================================================*/
template <class T>
T norma ( const Vec_2<T> &v )
{
	return T( sqrt( norma_quadrada( v ) ) );
}
/*===============================================================================================================================*/
template <class T>
T norma ( const Vec_3<T> &v )
{
	return T( sqrt( norma_quadrada( v ) ) );
}
/*===============================================================================================================================*/
template <class T>
T norma ( const Vec_4<T> &v )
{
	return T( sqrt( norma_quadrada( v ) ) );
}

/*===============================================================================================================================*/
template <class T>
Vec_2<T> unitario ( const Vec_2<T> &v )
{
	const T norma_v = norma( v );
	
	if ( norma_v != T(0) )
		return v / norma_v;
	else
		return v;
}
/*===============================================================================================================================*/
template <class T>
Vec_3<T> unitario ( const Vec_3<T> &v )
{
	const T norma_v = norma( v );
	
	if ( norma_v != T(0) )
		return v / norma_v;
	else
		return v;
}
/*===============================================================================================================================*/
template <class T>
Vec_4<T> unitario ( const Vec_4<T> &v )
{
	const T norma_v = norma( v );
	
	if ( norma_v != T(0) )
		return v / norma_v;
	else
		return v;
}
/*===============================================================================================================================*/
template <class T>
Vec_2<T> projecao ( const Vec_2<T> &v, const Vec_2<T> &v_proje )
{
	return ( produto_escalar( v, v_proje ) / norma_quadrada( v_proje ) ) * v_proje;
}
/*===============================================================================================================================*/
template <class T>
Vec_3<T> projecao ( const Vec_3<T> &v, const Vec_3<T> &v_proje )
{
	return ( produto_escalar( v, v_proje ) / norma_quadrada( v_proje ) ) * v_proje;
}
/*===============================================================================================================================*/
template <class T>
Vec_4<T> projecao ( const Vec_4<T> &v, const Vec_4<T> &v_proje )
{
	return ( produto_escalar( v, v_proje ) / norma_quadrada( v_proje ) ) * v_proje;
}
/*===============================================================================================================================*/
template <class T>
Vec_2<T> projecao_unitario ( const Vec_2<T> &v, const Vec_2<T> &v_proje_unitario )
{
	return produto_escalar( v, v_proje_unitario ) * v_proje_unitario;
}
/*===============================================================================================================================*/
template <class T>
Vec_3<T> projecao_unitario ( const Vec_3<T> &v, const Vec_3<T> &v_proje_unitario )
{
	return produto_escalar( v, v_proje_unitario ) * v_proje_unitario;
}
/*===============================================================================================================================*/
template <class T>
Vec_4<T> projecao_unitario ( const Vec_4<T> &v, const Vec_4<T> &v_proje_unitario )
{
	return produto_escalar( v, v_proje_unitario ) * v_proje_unitario;
}
/*===============================================================================================================================*/
template <class T>
Vec_2<T> projecao_inv ( const Vec_2<T> &v, const Vec_2<T> &v_proje )
{
	return ( produto_vetorial( v_proje, v ) / norma( v_proje ) );
}
/*===============================================================================================================================*/
template <class T>
Vec_3<T> projecao_inv ( const Vec_3<T> &v, const Vec_3<T> &v_proje )
{
	return ( produto_escalar( v, v_proje ) / norma_quadrada( v_proje ) ) * v_proje;
}
/*===============================================================================================================================*/
template <class T>
Vec_4<T> projecao_inv ( const Vec_4<T> &v, const Vec_4<T> &v_proje )
{
	return ( produto_escalar( v, v_proje ) / norma_quadrada( v_proje ) ) * v_proje;
}
/*===============================================================================================================================*/
template <class T>
Vec_2<T> projecao_inv_unitario ( const Vec_2<T> &v, const Vec_2<T> &v_proje_unitario )
{
	return produto_vetorial( v, v_proje_unitario ) * v_proje_unitario;
}
/*===============================================================================================================================*/
template <class T>
Vec_3<T> projecao_inv_unitario ( const Vec_3<T> &v, const Vec_3<T> &v_proje_unitario )
{
	return produto_escalar( v, v_proje_unitario ) * v_proje_unitario;
}
/*===============================================================================================================================*/
template <class T>
Vec_4<T> projecao_inv_unitario ( const Vec_4<T> &v, const Vec_4<T> &v_proje_unitario )
{
	return produto_escalar( v, v_proje_unitario ) * v_proje_unitario;
}
/*===============================================================================================================================*/
template <class T>
T cos_entre_vetores ( const Vec_2<T> &v1, const Vec_2<T> &v2 )
{
	return truncagem( produto_escalar( v1, v2 ) / T( sqrt( norma_quadrada( v1 ) * norma_quadrada( v2 ) ) ) );
}
/*===============================================================================================================================*/
template <class T>
T cos_entre_vetores ( const Vec_3<T> &v1, const Vec_3<T> &v2 )
{
	return truncagem( produto_escalar( v1, v2 ) / T( sqrt( norma_quadrada( v1 ) * norma_quadrada( v2 ) ) ) );
}
/*===============================================================================================================================*/
template <class T>
T cos_entre_vetores ( const Vec_4<T> &v1, const Vec_4<T> &v2 )
{
	return truncagem( produto_escalar( v1, v2 ) / T( sqrt( norma_quadrada( v1 ) * norma_quadrada( v2 ) ) ) );
}
/*===============================================================================================================================*/
template <class T>
T sen_entre_vetores ( const Vec_2<T> &v1, const Vec_2<T> &v2 )
{
	return truncagem( produto_vetorial( v1, v2 ) / T( sqrt( norma_quadrada( v1 ) * norma_quadrada( v2 ) ) ) );
}
/*===============================================================================================================================*/
template <class T>
T sen_entre_vetores ( const Vec_3<T> &v1, const Vec_3<T> &v2 )
{
	return truncagem( norma( produto_vetorial( v1, v2 ) ) / T( sqrt( norma_quadrada( v1 ) * norma_quadrada( v2 ) ) ) );
}
/*===============================================================================================================================*/
template <class T>
T sen_entre_vetores ( const Vec_4<T> &v1, const Vec_4<T> &v2 )
{
	return truncagem( norma( produto_vetorial( v1, v2 ) ) / T( sqrt( norma_quadrada( v1 ) * norma_quadrada( v2 ) ) ) );
}
/*===============================================================================================================================*/
template <template <class> class T, class U>
U angulo_cos ( const T<U> &v1, const T<U> &v2 )
{
	return R( acos( cos_entre_vetores( v1, v2 ) ) );
}
/*===============================================================================================================================*/
template <template <class> class T, class U>
U angulo_sen ( const T<U> &v1, const T<U> &v2 )
{
	return R( asin( sen_entre_vetores( v1, v2 ) ) );
}
/*===============================================================================================================================*/
template <class T>
T pseudoangulo ( const Vec_2<T> &v )
{
	T v_x = v.x(),
	  v_y = v.y();
	
	if ( std::abs( v_x ) <= std::abs( v_y ) ) {
		
		if ( v_y > 0 )
			return T(1) + ( T(1) - ( v_x / v_y ) );
		
		if ( v_y < 0 )
			return T(5) + ( T(1) - ( v_x / v_y ) );
		
	}
	
	if ( std::abs( v_x ) >= std::abs( v_y ) ) {
		
		if ( v_x > 0 )
			return ( ( v_y >= 0 )
			       ? T(1) - ( T(1) - ( v_y / v_x ) )
			       : T(7) + ( T(1) + ( v_y / v_x ) )
			       );
		
		if ( v_x < 0 )
			return T(3) + ( T(1) + ( v_y / v_x ) );
		
	}
	
	return T( nan("") );
}
/*===============================================================================================================================*/
template <class T>
T pseudoangulo ( const Vec_3<T> &v )
{

}
/*===============================================================================================================================*/
template <class T>
T pseudoangulo ( const Vec_4<T> &v )
{

}
/*===============================================================================================================================*/
template <class T>
T truncagem ( T valor )
{
	valor = ( valor < T(-1) ) ? T(-1) :
	        ( valor > T( 1) ) ? T( 1)  :
	        valor;
	
	return valor;
}
/*===============================================================================================================================*/
template <class T>
T truncagem ( T valor, T valor_max, T valor_min )
{
	valor = ( valor < valor_min ) ? valor_min :
	        ( valor > valor_max ) ? valor_max :
	        valor;
	
	return valor;
}
/*===============================================================================================================================*/
template <class T>
Vec_3<T> vetor_reflexao ( const Vec_3<T> &vetor, const Vec_3<T> &normal )
{
	 //Calcula o vetor unitário da normal, o vetor apontando para o observador e do ponto à luz
    const Vec_3<T> n = normal;
    const Vec_3<T> v = unitario( vetor );
    //Projeta o vetor da luz no vetor normal, inverte e usa-o para espelhar o vetor da luz
    const Vec_3<T> v_proj = -projecao_unitario( v, n );
    const Vec_3<T> vetor_invertido = v + ( T(2) * v_proj );

	return vetor_invertido;
}
/*===============================================================================================================================*/
template <class T>
Vec_3<T> vetor_refracao ( const Vec_3<T> &vetor, const Vec_3<T> &normal, T indice_meio_1, T indice_meio_2 )
{
	T divisao_indices_meios = indice_meio_1 / indice_meio_2;
	T angulo_v_n = produto_escalar( vetor, normal );
	T sen_ang_2 = ( indice_meio_1 * indice_meio_1 ) * ( 1 - ( angulo_v_n * angulo_v_n ) );

	return ( vetor * angulo_v_n )
	     + ( ( divisao_indices_meios * angulo_v_n )
		   - T( sqrt( 1 - sen_ang_2 ) ) ) * normal;
}
/*===============================================================================================================================*/