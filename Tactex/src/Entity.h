//
// Created by Brett Beers on 1/17/14.
// Copyright (c) 2014 Brett Beers. All rights reserved.
//

#ifndef __Entity_H_
#define __Entity_H_

#include <glm/glm.hpp>

class Entity {
public:
    Entity();
    Entity(Entity& entity);
    virtual ~Entity();

    glm::vec3 pos;
    glm::vec3 size;
};


#endif //__Entity_H_
