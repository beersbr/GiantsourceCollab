//
// Created by Brett Beers on 1/17/14.
// Copyright (c) 2014 Brett Beers. All rights reserved.
//


#include "Entity.h"

Entity::Entity()
{
    pos = glm::vec3();
    size = glm::vec3();
}

Entity::Entity(Entity &entity)
{
    pos = entity.pos;
    size = entity.size;
}

Entity::~Entity()
{

}