//
// Created by Brett Beers on 8/19/13.
// Copyright (c) 2013 Brett Beers. All rights reserved.
//

#ifndef __Vector_H_
#define __Vector_H_

#ifdef _WIN32
#define _USE_MATH_DEFINES
#endif

#ifdef _WIN64
#define _USE_MATH_DEFINES
#endif

#include <iostream>
#include <assert.h>
#include <math.h>

const double PI = M_PI;

class Vector {
public:
    Vector();
    Vector(const float x_, const float y_, const float z_);
    Vector(const Vector& v);
    ~Vector();

    bool operator==(const Vector& v) const;

    Vector& operator=(const Vector& v);
    const Vector operator+(const Vector& v) const;
    const Vector operator-(const Vector& v) const;

    // performs the cross product
    const Vector operator*(const Vector& v) const;
    const Vector operator/(const Vector& v) const;

    const Vector operator+(const float s) const;
    const Vector operator-(const float s) const;
    const Vector operator*(const float s) const;
    const Vector operator/(const float s) const;

    Vector& operator+=(const Vector& v);
    Vector& operator-=(const Vector& v);

    // performs the cross product
    Vector& operator*=(const Vector& v);
    Vector& operator/=(const Vector& v);

    Vector& operator+=(const float s);
    Vector& operator-=(const float s);
    Vector& operator*=(const float s);
    Vector& operator/=(const float s);

    float magnitude() const;

    // creates a new vector representing the unit vector of the given Vector
    const Vector toUnit() const;

    // rotates self around the given axis by the given angle
    Vector rotate(const Vector& axis, const float angle) const;

    static Vector crossProduct(const Vector& a, const Vector& b);
    static float dotProduct(const Vector& a, const Vector& b);

public:
    float x, y, z;

};

const Vector VECTOR_AXIS_X = Vector(1, 0, 0);
const Vector VECTOR_AXIS_Y = Vector(0, 1, 0);
const Vector VECTOR_AXIS_Z = Vector(0, 0, 1);

#endif //__Vector_H_
