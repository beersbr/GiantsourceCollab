//
// Created by Brett Beers on 8/19/13.
// Copyright (c) 2013 ___FULLUSERNAME___. All rights reserved.
//
// To change the template use AppCode | Preferences | File Templates.
//


#include "Vector.h"

Vector::Vector()
{
    x = y = z = 0;
}

Vector::Vector(const float x_, const float y_, const float z_)
{
    x = x_;
    y = y_;
    z = z_;
}

Vector::Vector(const Vector &v)
{
    x = v.x;
    y = v.y;
    z = v.z;
}

Vector::~Vector()
{
    x = y = z = 0;
}

bool Vector::operator==(const Vector& v) const
{
    if(this == &v)
        return true;

    if(x == v.x && y == v.y && z == v.z)
        return true;

    return false;
}

Vector& Vector::operator=(const Vector& v)
{
    if(this == &v)
        return *this;

    x = v.x;
    y = v.y;
    z = v.z;
    return *this;
}

const Vector Vector::operator+(const Vector& v) const
{
    Vector vt = Vector(v.x + x, v.y + y, v.z + z);
    return vt;
}

const Vector Vector::operator-(const Vector& v) const
{
    Vector vt = Vector(x - v.x, y-v.y, z-v.z);
    return vt;
}

const Vector Vector::operator*(const Vector& v) const
{
    Vector* vt = new Vector(x*v.x, y*v.y, z*v.z);
    return *vt;
}

// TODO: Possible division by zero here.
const Vector Vector::operator/(const Vector& v) const
{
    assert(v.x != 0);
    assert(v.y != 0);
    assert(v.z != 0);

    Vector* vt = new Vector(x / v.x, y / v.y, z / v.z);
    return *vt;
}

const Vector Vector::operator+(const float s) const
{
    Vector* vt = new Vector(x+s, y+s, z+s);
    return *vt;
}

const Vector Vector::operator-(const float s) const
{
    Vector* vt = new Vector(x-s, y-s, z-s);
    return *vt;
}

const Vector Vector::operator*(const float s) const
{
    Vector* vt = new Vector(x*s, y*s, z*s);
    return *vt;
}

const Vector Vector::operator/(const float s) const
{
    assert(s != 0);

    Vector* vt = new Vector(x/s, y/s, z/s);
    return *vt;
}

Vector& Vector::operator+=(const Vector& v)
{
    x += v.x;
    y += v.y;
    z += v.z;
    return *this;
}

Vector& Vector::operator-=(const Vector& v)
{
    x -= v.x;
    y -= v.y;
    z -= v.z;
    return *this;
}

Vector& Vector::operator*=(const Vector& v)
{
    x *= v.x;
    y *= v.y;
    z *= v.z;
    return *this;
}

Vector& Vector::operator/=(const Vector& v)
{
    assert(v.x != 0);
    assert(v.y != 0);
    assert(v.z != 0);

    x /= v.x;
    y /= v.y;
    z /= v.z;
    return *this;
}

Vector& Vector::operator+=(const float s)
{
    x += s;
    y += s;
    z += s;
    return *this;
}

Vector& Vector::operator-=(const float s)
{
    x -= s;
    y -= s;
    z -= s;
    return *this;
}

Vector& Vector::operator*=(const float s)
{
    x *= s;
    y *= s;
    z *= s;
    return *this;
}

Vector& Vector::operator/=(const float s)
{
    assert(s != 0);

    x /= s;
    y /= s;
    z /= s;
    return *this;
}

float Vector::magnitude() const
{
    return (sqrtf(x*x + y*y + z*z));
}

const Vector Vector::toUnit() const
{
    float m = this->magnitude();

    assert(m != 0);

    Vector tv = Vector(x/m, y/m, z/m);
    return tv;
}

Vector Vector::rotate(const Vector& axis, const float angle) const
{
    Vector t = (*this);

    // NOTE: this is here because the cos(PI/2) is not so accurate
    double cos_angle = (cos(angle) < 1/1000000.0f) ? 0.0f : cos(angle);

    t = ((t - axis * (axis * t)) * cos_angle) + ((crossProduct(t, axis)) * sin(angle)) + (axis * (axis * t));
    return t;
}

// static
Vector Vector::crossProduct(const Vector& a, const Vector& b)
{
    float x = (a.y*b.z - b.y*a.z);
    float y = (a.z*b.x - a.x*b.z);
    float z = (a.x*b.y - a.y*b.x);
    Vector vt = Vector(x, y, z);
    return vt;
}

// static
float Vector::dotProduct(const Vector& a, const Vector& b)
{
//    Vector aa = a.toUnit();
//    Vector bb = b.toUnit();
//
//    float dp = (aa.x * bb.x) + (aa.y * bb.y) + (aa.z * bb.z);
    float dp = (a.x * b.x) + (a.y * b.y) + (a.z * b.z);
    return dp;
}
