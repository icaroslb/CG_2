template <class T>
Vec_3<T>::Vec_3 ( T x, T y, T z )
: _x( x )
, _y( y )
, _z( z )
{}
/*===============================================================================================================================*/
template <class T>
T& Vec_3<T>::x () { return _x; }
/*===============================================================================================================================*/
template <class T>
const T& Vec_3<T>::x () const { return _x; }
/*===============================================================================================================================*/
template <class T>
T& Vec_3<T>::y () { return _y; }
/*===============================================================================================================================*/
template <class T>
const T& Vec_3<T>::y () const { return _y; }
/*===============================================================================================================================*/
template <class T>
T& Vec_3<T>::z () { return _z; }
/*===============================================================================================================================*/
template <class T>
const T& Vec_3<T>::z () const { return _z; }
/*===============================================================================================================================*/
template <class T>
T& Vec_3<T>::operator[] ( int i ) { return coord[i]; }
/*===============================================================================================================================*/
template <class T>
const T& Vec_3<T>::operator[] ( int i ) const { return coord[i]; }
/*===============================================================================================================================*/
template <class T>
Vec_3<T> Vec_3<T>::operator + ( const Vec_3<T> &v ) const
{
	return Vec_3<T>( _x + v._x, _y + v._y, _z + v._z );
}
/*===============================================================================================================================*/
template <class T>
Vec_3<T> Vec_3<T>::operator - ( const Vec_3<T> &v ) const
{
	return Vec_3<T>( _x - v._x, _y - v._y, _z - v._z );
}
/*===============================================================================================================================*/
template <class T>
Vec_3<T> Vec_3<T>::operator * ( const Vec_3<T> &v ) const
{
	return Vec_3<T>( _x * v._x, _y * v._y, _z * v._z );
}
/*===============================================================================================================================*/
template <class T>
Vec_3<T> Vec_3<T>::operator + ( T c ) const
{
	return Vec_3<T>( _x + c, _y + c, _z + c );
}
/*===============================================================================================================================*/
template <class T>
Vec_3<T> Vec_3<T>::operator - ( T c ) const
{
	return Vec_3<T>( _x - c, _y - c, _z - c );
}
/*===============================================================================================================================*/
template <class T>
Vec_3<T> Vec_3<T>::operator * ( T c ) const
{
	return Vec_3<T>( _x * c, _y * c, _z * c );
}
/*===============================================================================================================================*/
template <class T>
Vec_3<T> Vec_3<T>::operator / ( T c ) const
{
	c = T(1) / c;
	
	return Vec_3<T>( _x * c, _y * c, _z * c );
}
/*===============================================================================================================================*/
template <class T>
Vec_3<T>& Vec_3<T>::operator = ( const Vec_3<T> &v )
{
	_x = v._x;
	_y = v._y;
	_z = v._z;
	
	return *this;
}
/*===============================================================================================================================*/
template <class T>
Vec_3<T>& Vec_3<T>::operator += ( const Vec_3<T> &v )
{
	_x += v._x;
	_y += v._y;
	_z += v._z;
	
	return *this;
}
/*===============================================================================================================================*/
template <class T>
Vec_3<T>& Vec_3<T>::operator -= ( const Vec_3<T> &v )
{
	_x -= v._x;
	_y -= v._y;
	_z -= v._z;
	
	return *this;
}
/*===============================================================================================================================*/
template <class T>
Vec_3<T>& Vec_3<T>::operator *= ( const Vec_3<T> &v )
{
	_x *= v._x;
	_y *= v._y;
	_z *= v._z;
	
	return *this;
}
/*===============================================================================================================================*/
template <class T>
Vec_3<T>& Vec_3<T>::operator += ( T c )
{
	_x += c;
	_y += c;
	_z += c;
	
	return *this;
}
/*===============================================================================================================================*/
template <class T>
Vec_3<T>& Vec_3<T>::operator -= ( T c )
{
	_x -= c;
	_y -= c;
	_z -= c;
	
	return *this;
}
/*===============================================================================================================================*/
template <class T>
Vec_3<T>& Vec_3<T>::operator *= ( T c )
{
	_x *= c;
	_y *= c;
	_z *= c;
	
	return *this;
}
/*===============================================================================================================================*/
template <class T>
Vec_3<T>& Vec_3<T>::operator /= ( T c )
{
	c = T(1) / c;
	
	_x *= c;
	_y *= c;
	_z *= c;
	
	return *this;
}
/*===============================================================================================================================*/
template <class T>
Vec_3<T> operator + ( const Vec_3<T> &v )
{
	return Vec_3<T>( +v._x, +v._y, +v._z );
}
/*===============================================================================================================================*/
template <class T>
Vec_3<T> operator - ( const Vec_3<T> &v )
{
	return Vec_3<T>( -v._x, -v._y, -v._z );
}
/*===============================================================================================================================*/
template <class T>
Vec_3<T> operator * ( T c, const Vec_3<T> &v ) {
	return Vec_3<T>( v._x * c, v._y * c, v._z * c );
}
/*===============================================================================================================================*/
template <class T>	
Vec_3<T>& operator << ( Vec_3<T> &vet, T dado ) {
	
	vet._x = dado;
	
	return vet;
}
/*===============================================================================================================================*/
template <class T>	
Vec_3<T>& operator , ( Vec_3<T> &vet, T dado ) {
	static size_t indice   = 1;
	static auto   id_vetor = &vet;
	
	if ( id_vetor != &vet ) {
		indice = 1;
		id_vetor = &vet;
	}
	
	switch ( indice ) {
		case 1: vet._y = dado; indice++  ; break;
		case 2: vet._z = dado; indice = 1; break;
		default: break;
	}
	
	return vet;
}
/*===============================================================================================================================*/
template <class T>
std::ostream& operator << (std::ostream &os, const Vec_3<T> &v ) {
	return os << "[ " << v._x << ", " << v._y << ", " << v._z << " ]";
}
/*===============================================================================================================================*/