#ifndef VEC2D_H
#define VEC2D_H

//! \file Vec2d.h
//! \author J Mills
//! \date 1/1/2014 

class Vec2d {
public:
	int x;
	int y;
	
	Vec2d(int xx, int yy) : x(xx), y(yy) {}
	Vec2d() : x(0), y(0) {}
	
	//Overloaded Unary
	Vec2d operator-() { return Vec2d(-x, -y); }
	
	//Overloaded Binary Vec2d
	Vec2d operator=(const Vec2d &v) { x = v.x; y = v.y; return *this; }
	Vec2d operator+(const Vec2d &v) { return Vec2d(x+v.x, y+v.y); }
	Vec2d operator-(const Vec2d &v) { return Vec2d(x-v.x, y-v.y); }
	Vec2d operator*(const Vec2d &v) { return Vec2d(x*v.x, y*v.y); }
	Vec2d operator/(const Vec2d &v) { return Vec2d(x/v.x, y/v.y); }
	
	Vec2d operator+=(const Vec2d &v) { x += v.x; y += v.y; return *this; }
	Vec2d operator-=(const Vec2d &v) { x -= v.x; y -= v.y; return *this; }
	Vec2d operator*=(const Vec2d &v) { x *= v.x; y *= v.y; return *this; }
	Vec2d operator/=(const Vec2d &v) { x /= v.x; y /= v.y; return *this; }
	
	//Overloaded Binary int
	Vec2d operator+(const int &i) { return Vec2d(x+i, y+i); }
	Vec2d operator-(const int &i) { return Vec2d(x-i, y-i); }
	Vec2d operator*(const int &i) { return Vec2d(x*i, y*i); }
	Vec2d operator/(const int &i) { return Vec2d(x/i, y/i); }
	
	Vec2d operator+=(const int &i) { x += i; y += i; return *this; }
	Vec2d operator-=(const int &i) { x -= i; y -= i; return *this; }
	Vec2d operator*=(const int &i) { x *= i; y *= i; return *this; }
	Vec2d operator/=(const int &i) { x /= i; y /= i; return *this; }
	
	//Overloaded Comparison Vec2d
	bool operator==(const Vec2d &v) { return ((x == v.x)&&(y == v.y)); }
	bool operator!=(const Vec2d &v) { return ((x != v.x)||(y != v.y)); }
};

#endif //VEC2D_H