//
// Created by Brett Beers on 1/17/14.
// Copyright (c) 2014 Brett Beers. All rights reserved.
//



#ifndef __Camera_H_
#define __Camera_H_

#include <glm/glm.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include "KeyboardHandler.h"
#include "Entity.h"

class Camera : public Entity{
public:
    Camera();
    Camera(const Camera &c);
    Camera(const glm::vec3 position, const glm::vec3 lookAtVector);
    virtual ~Camera();

    virtual void draw() const;
    virtual int update();

    glm::mat4 getViewMatrix() const;

public:
    glm::vec3 dir;

};


#endif //__Camera_H_
