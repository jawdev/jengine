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
		for( int k = 0; k < 4; k++ ) temp[k] = data[k][i];
		return temp;
	}

	float* col( const unsigned int& j ) {
		float* temp = new float[4];
		for( int k = 0; k < 4; k++ ) temp[k] = data[j][k];
		return temp;
	}

	float at( const unsigned int& i, const unsigned int& j ) {
		if( i > 3 || j > 3 ) return 0;
		return data[j][i];
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
		data[j][i] = val;
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
		  data[j][i] = m.data[j][0]*cp.data[0][i]+m.data[j][1]*cp.data[1][i]+m.data[j][2]*cp.data[2][i]+m.data[j][3]*cp.data[3][i];
		return *this;
	}
	const mat operator*( const mat& m ) const {
		mat result = *this;
		result *= m;
		return result;
	}

	friend ostream& operator<<( ostream& os, const mat& m );

	float* float_data() { return (float*)this; }
	GLfloat* glfloat_data() { return (GLfloat*)this; }
	unsigned int glfloat_size() { return sizeof( GLfloat )*16; }

};

inline ostream& operator<<( ostream& os, const mat& m ) {
	os << "========================================";
	os << "========================================" << endl;
	for( int i = 0; i < 4; i++ ) {
		for( int j = 0; j < 4; j++ ) {
			os << setw( 20 );
			os << m.data[j][i];
		}
		os << endl;
	}
	os << "========================================";
	os << "========================================" << endl;
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
	float* float_data() { return (float*)this; }
	GLfloat* glfloat_data() { return (GLfloat*)this; }
	unsigned int glfloat_size() { return sizeof( GLfloat)*4; }

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
		x = m.data[0][0]*cp.x + m.data[1][0]*cp.y + m.data[2][0]*cp.z + m.data[3][0]*cp.w;
		y = m.data[0][1]*cp.x + m.data[1][1]*cp.y + m.data[2][1]*cp.z + m.data[3][1]*cp.w;
		z = m.data[0][2]*cp.x + m.data[1][2]*cp.y + m.data[2][2]*cp.z + m.data[3][2]*cp.w;
		w = m.data[0][3]*cp.x + m.data[1][3]*cp.y + m.data[2][3]*cp.z + m.data[3][3]*cp.w;
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
	float* float_data() { return (float*)this; }
	GLfloat* glfloat_data() { return (GLfloat*)this; }
	unsigned int glfloat_size() { return sizeof( GLfloat )*4; }

};

inline ostream& operator<<( ostream& os, const vec& v ) {
	os << "<" << v.x << "," << v.y << "," << v.z << "," << v.w << ">";
	return os;
}

///////////////////////////////////////////////// vertices

struct vertices {
	
	vertices() {
		vecs.clear();
	}

	~vertices() {
		vecs.clear();
	}

	void add( vec v ) {
		vecs.push_back( v );
	}
	void add( float x=0, float y=0, float z=0, float w=1 ) {
		vecs.push_back( vec( x, y, z, w ) );
	}

	GLfloat* glfloat_data() {
		GLfloat* floatData = new GLfloat[vecs.size()*4];
		unsigned int j = 0;
		for( unsigned int i = 0; i < vecs.size(); i++ ) {
			floatData[j++] = (GLfloat)vecs[i].x;
			floatData[j++] = (GLfloat)vecs[i].y;
			floatData[j++] = (GLfloat)vecs[i].z;
			floatData[j++] = (GLfloat)vecs[i].w;
		}
		return &floatData[0];
	}

	void glfloat_write( GLfloat* pG ) {
		unsigned int j = 0;
		for( unsigned int i = 0; i < vecs.size(); i++ ) {
			pG[j++] = (GLfloat)vecs[i].x;
			pG[j++] = (GLfloat)vecs[i].y;
			pG[j++] = (GLfloat)vecs[i].z;
			pG[j++] = (GLfloat)vecs[i].w;
		}
	}

	unsigned int glfloat_size() { return sizeof( GLfloat )*vecs.size()*4; }

	vector< vec > vecs;
};

///////////////////////////////////////////////// indices

struct indices {

	indices() { shorts.clear(); }
	~indices() { shorts.clear(); }

	void add( unsigned short a, unsigned short b, unsigned short c ) {
		shorts.push_back( a );
		shorts.push_back( b );
		shorts.push_back( c );
	}

	GLushort* glushort_data() {
		GLushort* shortData = new GLushort[shorts.size()];
		for( unsigned int i = 0; i < shorts.size(); i++ ) shortData[i] = (GLushort)shorts[i];
		return shortData;
	}

	void glushort_write( GLushort* pG ) {
		unsigned int j = 0;
		for( unsigned int i = 0; i < shorts.size(); i++ ) {
			pG[j++] = (GLushort)shorts[i];
		}
	}

	unsigned int glushort_size() { return sizeof( GLushort )*shorts.size(); }

	vector< unsigned short > shorts;
};

///////////////////////////////////////////////// vmath

struct vmath {

	static inline vec norm( const vec& a ) {
		float mag = sqrt( a.x*a.x+a.y*a.y+a.z*a.z );
		if( mag == 0 ) return vec( 0, 0, 0, 1 );
		else return vec( a.x/mag, a.y/mag, a.z/mag, 1 );
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

	static inline void mat_translation( mat* m, const vec& v ) {
		m->identity();
		m->set( 0, 3, v.x );
		m->set( 1, 3, v.y );
		m->set( 2, 3, v.z );
	}

	static inline mat mat_translation( const vec& v ) {
		mat* pM = new mat;
		mat_translation( pM, v );
		return *pM;
	}

	static inline void mat_rotation_x( mat* m, float f ) {
		m->identity();
		float cosAng = cos( f );
		float sinAng = sin( f );
		m->set( 1, 1, cosAng );
		m->set( 1, 2, -sinAng );
		m->set( 2, 1, sinAng );
		m->set( 2, 2, cosAng );
	}

	static inline void mat_rotation_y( mat* m, float f ) {
		m->identity();
		float cosAng = cos( f );
		float sinAng = sin( f );
		m->set( 0, 0, cosAng );
		m->set( 0, 2, sinAng );
		m->set( 2, 0, -sinAng );
		m->set( 2, 2, cosAng );
	}

	static inline void mat_rotation_z( mat* m, float f ) {
		m->identity();
		float cosAng = cos( f );
		float sinAng = sin( f );
		m->set( 0, 0, cosAng );
		m->set( 0, 1, sinAng );
		m->set( 1, 0, -sinAng );
		m->set( 1, 1, -cosAng );
	}

	static inline void mat_rotation( mat* m, const vec& v ) {
		mat mx, my, mz;
		if( v.x != 0 ) mat_rotation_x( &mx, v.x );
		if( v.y != 0 ) mat_rotation_y( &my, v.y );
		if( v.z != 0 ) mat_rotation_z( &mz, v.z );
		*m = mz*mx*my;
	}

	static inline void perspective( mat* m, float left, float right, float bottom, float top, float n, float f ) {
		m->identity();
		if( right == left || top == bottom || n == f || n < 0 || f < 0 ) return;
		m->set( 0, 0, ( 2.0f*n )/( right-left ) );
		m->set( 0, 2, ( right+left )/( right-left ) );
		m->set( 1, 1, ( 2.0f*n )/( top-bottom ) );
		m->set( 1, 2, ( top+bottom )/( top-bottom ) );
		m->set( 2, 2, -( f+n )/( f-n ) );
		m->set( 2, 3, -( 2.0f*f*n )/( f-n ) );
		m->set( 3, 2, -1 );
		m->set( 3, 3, 0 );
	}

	static inline void orthographic( mat* m, float left, float right, float bottom, float top, float n, float f ) {
		m->identity();
		if( right == left || top == bottom || n == f || n < 0 || f < 0 ) return;
		m->set( 0, 0, ( 2.0f*n )/( right-left ) );
		m->set( 0, 3, -( right+left )/( right-left ) );
		m->set( 1, 1, 2.0f/( top-bottom ) ) ;
		m->set( 2, 3, -( top+bottom )/( top-bottom ) );
		m->set( 2, 2, -2.0f/( f-n ) );
		m->set( 2, 3, -( f+n )/( f-n ) );
	}

};


} //jengine
#endif //__JENGINE_VMATH_H__
