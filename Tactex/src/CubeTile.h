//
// Created by Brett Beers on 1/17/14.
// Copyright (c) 2014 Brett Beers. All rights reserved.
//



#ifndef __CubeTile_H_
#define __CubeTile_H_

#include "Entity.h"
#include <OpenGL/gl3.h>

class CubeTile : public Entity{
public:
    static std::vector<CubeTile*> cubeTiles;

    static const GLfloat cubeCoords[];
    static const GLfloat cubeFaceNormals[];

public:
    CubeTile();
    CubeTile(const CubeTile& ct);
    ~CubeTile();

    void drawAll() const;

    virtual void draw() const;
    virtual int update();

private:
    static GLuint cubeVOA;
    static GLuint cubeVBO;
    static GLuint cubeIBO;

    static bool initd;
};


#endif //__CubeTile_H_
