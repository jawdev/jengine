/*******************************************************
 * Created by JAW Development
 * jawdev > jengine > math.h
*******************************************************/
#ifndef __JENGINE_MATH_H__
#define __JENGINE_MATH_H__
namespace jengine {

///////////////////////////////////////////////// vec

struct vec {

	vec( float _x = 0, float _y = 0, float _z = 0, float _w = 0, bool _lock_w = true ) {
		x = _x;
		y = _y;
		z = _z;
		w = _w;
		lock_w = _lock_w;
	}

	float x;
	float y;
	float z;
	float w;
	bool lock_w;

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

	const vec operator*( const float f ) const {
		vec result = *this;
		result *= f;
		return result;
	}

	const vec operator/( const float f ) const {
		vec result = *this;
		result /= f;
		return result;
	}

};



} //jengine
#endif //__JENGINE_MATH_H__
