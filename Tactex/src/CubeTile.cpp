//
// Created by Brett Beers on 1/17/14.
// Copyright (c) 2014 Brett Beers. All rights reserved.
//


#include "CubeTile.h"

std::vector<CubeTile*> CubeTile::cubeTiles = std::vector<CubeTile*>();

GLuint CubeTile::cubeVOA = -1;
GLuint CubeTile::cubeVBO = -1;
GLuint CubeTile::cubeIBO = -1;

bool CubeTile::initd = false;

const GLfloat CubeTile::cubeCoords[] = {
        // west
        -1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f,  1.0f,
        -1.0f,  1.0f,  1.0f,

        -1.0f, -1.0f, -1.0f,
        -1.0f,  1.0f,  1.0f,
        -1.0f,  1.0f, -1.0f,

        // bottom
         1.0f, -1.0f,  1.0f,
        -1.0f, -1.0f,  1.0f,
        -1.0f, -1.0f, -1.0f,

         1.0f, -1.0f,  1.0f,
        -1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,

        // back
         1.0f,  1.0f, -1.0f,
        -1.0f, -1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,

         1.0f,  1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f, -1.0f,

        // front
        -1.0f,  1.0f,  1.0f,
        -1.0f, -1.0f,  1.0f,
         1.0f, -1.0f,  1.0f,

         1.0f,  1.0f,  1.0f,
        -1.0f,  1.0f,  1.0f,
         1.0f, -1.0f,  1.0f,

        // right
         1.0f,  1.0f,  1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f,  1.0f, -1.0f,

         1.0f, -1.0f, -1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f, -1.0f,  1.0f,

        // top
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,

         1.0f,  1.0f,  1.0f,
        -1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f,  1.0f
};

const GLfloat CubeTile::cubeFaceNormals[] = {

};

CubeTile::CubeTile(){
    if(!initd)
    {
        glGenVertexArrays(1, &CubeTile::cubeVOA);
        glBindVertexArray(CubeTile::cubeVOA);


        glGenBuffers(1, &CubeTile::cubeVBO);
        glBindBuffer(GL_ARRAY_BUFFER, CubeTile::cubeVBO);
        glBufferData(GL_ARRAY_BUFFER, (36*3)*sizeof(GLfloat), CubeTile::cubeCoords, GL_STATIC_DRAW);

//        glGenBuffers(1, &CubeTile::cubeIBO);
//        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, CubeTile::cubeIBO);
//        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof())

        initd = true;
    }
}

void CubeTile::drawAll() const
{
}

void CubeTile::draw() const
{

}

int CubeTile::update()
{
    return 0;
}