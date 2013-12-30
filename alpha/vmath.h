/*******************************************************
 * Created by JAW Development
 * jawdev > jengine > math.h
*******************************************************/
#ifndef __JENGINE_VMATH_H__
#define __JENGINE_VMATH_H__
namespace jengine {

///////////////////////////////////////////////// mat

struct mat {

	float data[4][4];

	mat() {
		identity();
	}

	float* row( const unsigned int& i ) {
		float* temp = new float[4];
		for( int k = 0; k < 4; k++ ) temp[k] = data[i][k];
		return temp;
	}

	float* col( const unsigned int& j ) {
		float* temp = new float[4];
		for( int k = 0; k < 4; k++ ) temp[k] = data[k][j];
		return temp;
	}

	float at( const unsigned int& i, const unsigned int& j ) {
		if( i > 3 || j > 3 ) return 0;
		return data[i][j];
	}

	void zero() {
		for( int i = 0; i < 4; i++ )
		 for( int j = 0; j < 4; j++ )
		  data[i][j] = 0;
	}

	void identity() {
		for( int i = 0; i < 4; i++ ) {
			for( int j = 0; j < 4; j++ ) {
				if( i == j ) data[i][j] = 1;
				else data[i][j] = 0;
			}
		}
	}

	void set( const unsigned int& i, const unsigned int& j, const float& val ) {
		data[i][j] = val;
	}

	mat& operator=( const mat& m ) {
		if( this == &m ) return *this;
		for( int i = 0; i < 4; i++ )
		 for( int j = 0; j < 4; j++ )
		  data[i][j] = m.data[i][j];
		return *this;
	}

	mat& operator*=( const mat& m ) {
		mat cp = *this;
		for( int i = 0; i < 4; i++ )
		 for( int j = 0; j < 4; j++ )
		  data[i][j] = m.data[i][0]*cp.data[0][j]+m.data[i][1]*cp.data[1][j]+m.data[i][2]*cp.data[2][j]+m.data[i][3]*cp.data[3][j];
		return *this;
	}
	const mat operator*( const mat& m ) const {
		mat result = *this;
		result *= m;
		return result;
	}

	friend ostream& operator<<( ostream& os, const mat& m );

};

inline ostream& operator<<( ostream& os, const mat& m ) {
	os << "========================================" << endl;
	for( int i = 0; i < 4; i++ ) {
		for( int j = 0; j < 4; j++ ) {
			os << setw( 10 );
			os << m.data[i][j];
		}
		os << endl;
	}
	os << "========================================";
	return os;
}

///////////////////////////////////////////////// quat

struct quat {
	
	quat( float _w = 0, float _x = 0, float _y = 0, float _z = 0 ) {
		w = _w;
		x = _x;
		y = _y;
		z = _z;
	}

	float w;
	float x;
	float y;
	float z;

	friend ostream& operator<<( ostream& os, const quat& q );

};

inline ostream& operator<<( ostream& os, const quat& q ) {
	os << "[" << q.w << "," << q.x << "," << q.y << "," << q.z << "]";
	return os;
}

///////////////////////////////////////////////// vec

struct vec {

	float x;
	float y;
	float z;
	float w;
	bool lock_w;

	vec( float _x = 0, float _y = 0, float _z = 0, float _w = 1, bool _lock_w = true ) {
		x = _x;
		y = _y;
		z = _z;
		w = _w;
		lock_w = _lock_w;
	}

	vec& operator=( const vec& v ) {
		if( this == &v ) return *this;
		x = v.x;
		y = v.y;
		z = v.z;
		w = v.w;
		return *this;
	}

	vec& operator+=( const vec& v ) {
		x += v.x;
		y += v.y;
		z += v.z;
		if( !lock_w ) w += v.w;
		return *this;
	}

	vec& operator-=( const vec& v ) {
		x -= v.x;
		y -= v.y;
		z -= v.z;
		if( !lock_w ) w -= v.w;
		return *this;
	}

	vec& operator*=( const float f ) {
		x *= f;
		y *= f;
		z *= f;
		if( !lock_w ) w *= f;
		return *this;
	}

	vec& operator*=( const mat& m ) {
		vec cp = *this;
		x = m.data[0][0]*cp.x + m.data[0][1]*cp.y + m.data[0][2]*cp.z + m.data[0][3]*cp.w;
		y = m.data[1][0]*cp.x + m.data[1][1]*cp.y + m.data[1][2]*cp.z + m.data[1][3]*cp.w;
		z = m.data[2][0]*cp.x + m.data[2][1]*cp.y + m.data[2][2]*cp.z + m.data[2][3]*cp.w;
		w = m.data[3][0]*cp.x + m.data[3][1]*cp.y + m.data[3][2]*cp.z + m.data[3][3]*cp.w;
		return *this;
	}

	vec& operator*=( const quat& q ) {
		*this = ( vec( q.x, q.y, q.z, 1 )*( q.x*x+q.y*y+q.z*z )*2.0f )+( (*this)*( q.w*q.w-( q.x*q.x+q.y*q.y+q.z*q.z ) ) )+( vec( q.y*z-q.z*y, -( q.x*z-q.z*x ), q.x*y-q.y*x, 1)*q.w*2.0f );
		return *this;
	}

	vec& operator/=( const float f ) {
		x /= f;
		y /= f;
		z /= f;
		if( !lock_w ) w /= f;
		return *this;
	}

	const vec operator+( const vec& v ) const {
		vec result = *this;
		result += v;
		return result;
	}

	const vec operator-( const vec& v ) const {
		vec result = *this;
		result -= v;
		return result;
	}

	const vec operator-() const {
		vec result = *this;
		result *= -1;
		return result;
	}

	const vec operator*( const float f ) const {
		vec result = *this;
		result *= f;
		return result;
	}

	const vec operator*( const mat& m ) const {
		vec result = *this;
		result *= m;
		return result;
	}

	const vec operator*( const quat& q ) const {
		vec result = *this;
		result *= q;
		return result;
	}

	const vec operator/( const float f ) const {
		vec result = *this;
		result /= f;
		return result;
	}

	friend ostream& operator<<( ostream& os, const vec& v);

};

inline ostream& operator<<( ostream& os, const vec& v ) {
	os << "<" << v.x << "," << v.y << "," << v.z << "," << v.w << ">";
	return os;
}

///////////////////////////////////////////////// vmath

struct vmath {

	static inline vec norm( const vec& a ) {
		float mag = sqrt( a.x*a.x+a.y*a.y+a.z*a.z );
		return vec( a.x/mag, a.y/mag, a.z/mag, 1 );
	}

	static inline vec cross( vec a, vec b ) {
		if( a.w != 1 ) a = norm( a );
		if( a.w != 1 ) b = norm( b );
		return vec( a.y*b.z-a.z*b.y, a.z*b.x-a.x*b.z, a.x*b.y-a.y*b.x, 1 );
	}

	static inline quat quat_from_axis_angle( const vec& axis, float angle ) {
		quat result;
		float halfAng = angle / -2.0f;
		float sinAng = sin( halfAng );
		vec n = ( axis.w == 1 ) ? axis : norm( axis );
		result.w = cos( halfAng );
		result.x = n.x*sinAng;
		result.y = n.y*sinAng;
		result.z = n.z*sinAng;
		return result;
	}

	static inline void mat_translation( const vec& v, mat* m ) {
		m->identity();
		m->set( 0, 3, v.x );
		m->set( 1, 3, v.y );
		m->set( 2, 3, v.z );
	}

	static inline mat mat_translation( const vec& v ) {
		mat* pM = new mat;
		mat_translation( v, pM );
		return *pM;
	}

	static inline void mat_rotation_x( float f, mat* m ) {
		m->identity();
		float cosAng = cos( f );
		float sinAng = sin( f );
		m->set( 1, 1, cosAng );
		m->set( 1, 2, -sinAng );
		m->set( 2, 1, sinAng );
		m->set( 2, 2, -cosAng );
	}

	static inline void mat_rotation_y( float f, mat* m ) {
		m->identity();
		float cosAng = cos( f );
		float sinAng = sin( f );
		m->set( 0, 0, cosAng );
		m->set( 0, 2, -sinAng );
		m->set( 2, 0, sinAng );
		m->set( 2, 2, -cosAng );
	}

	static inline void mat_rotation_z( float f, mat* m ) {
		m->identity();
		float cosAng = cos( f );
		float sinAng = sin( f );
		m->set( 0, 0, cosAng );
		m->set( 0, 1, -sinAng );
		m->set( 1, 0, sinAng );
		m->set( 1, 1, -cosAng );
	}

	static inline void mat_rotation( const vec& v, mat* m ) {
		mat mx, my, mz;
		mat_rotation_x( v.x, &mx );
		mat_rotation_y( v.y, &my );
		mat_rotation_z( v.z, &mz );
		*m = mx*my*mz;
	}

};


} //jengine
#endif //__JENGINE_VMATH_H__
