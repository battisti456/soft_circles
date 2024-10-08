/*
This file is based on code provided under Chan Jer Shyan under the MIT License,
however this exact version of this file is restricted to the same license as the rest of the repository.

The original header is included underneath.
*/
/*
Copyright (c) 2020 Chan Jer Shyan
Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:
The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#ifndef __VEC2_H__
#define __VEC2_H__

#define _USE_MATH_DEFINES

#include <cmath>

template <class T>
class vec2 {
public:
	T x, y;
	
	vec2() :x(0), y(0) {}
	vec2(T x, T y) : x(x), y(y) {}
	vec2(const vec2& v) : x(v.x), y(v.y) {}
	
	vec2& operator=(const vec2& v) {
		x = v.x;
		y = v.y;
		return *this;
	}
	
	vec2 operator+(const vec2& v) const {
		return vec2(x + v.x, y + v.y);
	}
	vec2 operator-(const vec2& v) const {
		return vec2(x - v.x, y - v.y);
	}
	vec2 operator-() const {
		return vec2(-x,-y);
	}
	
	vec2& operator+=(const vec2& v) {
		x += v.x;
		y += v.y;
		return *this;
	}
	vec2& operator-=(const vec2& v) {
		x -= v.x;
		y -= v.y;
		return *this;
	}
	
	vec2 operator+(double s) const {
		return vec2(x + s, y + s);
	}
	vec2 operator-(double s) const {
		return vec2(x - s, y - s);
	}
	vec2 operator*(double s) const {
		return vec2(x * s, y * s);
	}
	vec2 operator/(double s) const {
		return vec2(x / s, y / s);
	}
	
	
	vec2& operator+=(double s) {
		x += s;
		y += s;
		return *this;
	}
	vec2& operator-=(double s) {
		x -= s;
		y -= s;
		return *this;
	}
	vec2& operator*=(double s) {
		x *= s;
		y *= s;
		return *this;
	}
	vec2& operator/=(double s) {
		x /= s;
		y /= s;
		return *this;
	}
	
	void set(T x, T y) {
		this->x = x;
		this->y = y;
	}
	
	void rotate(double deg) {
		double theta = deg / 180.0 * M_PI;
		double c = cos(theta);
		double s = sin(theta);
		double tx = x * c - y * s;
		double ty = x * s + y * c;
		x = tx;
		y = ty;
	}
	
	vec2 normalize() const {
		T len = length();
		if (len == 0) return *this;
		return *this / len;
	}
	
	T dist(vec2 const& v) const {
		vec2 d(v.x - x, v.y - y);
		return d.length();
	}
	T length() const {
		return std::sqrt(x * x + y * y);
	}
	void truncate(double length) {
		double angle = atan2f(y, x);
		x = length * cos(angle);
		y = length * sin(angle);
	}
	
	vec2 ortho() const {
		return vec2(y, -x);
	}
	
	static T dot(const vec2 &v1, const vec2 &v2) {
		return v1.x * v2.x + v1.y * v2.y;
	}
	static T cross(const vec2 &v1, const vec2  &v2) {
		return (v1.x * v2.y) - (v1.y * v2.x);
	}
	static const vec2 zero;
	
};

template <class T>
vec2<T> operator*(T val, const vec2<T> & vec){
	return vec*val;
}

template <class T>
const vec2<T> vec2<T>::zero(0,0);


#endif