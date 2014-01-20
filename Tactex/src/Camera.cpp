//
// Created by Brett Beers on 1/17/14.
// Copyright (c) 2014 Brett Beers. All rights reserved.
//


#include "Camera.h"

Camera::Camera()
{
    pos = glm::vec3(0, 0, 0);
    dir = glm::vec3(0, 0, 0);
}

Camera::Camera(const glm::vec3 position, const glm::vec3 lookatVector)
{
    pos = position;
    dir = lookatVector;
}

Camera::Camera(Camera& camera)
{

}

Camera::~Camera()
{

}

void Camera::draw() const
{

}

int Camera::update()
{
    KeyboardHandler* keyboard = KeyboardHandler::getInstance();

    if(keyboard->keyDown(SDL_SCANCODE_A))
    {
        glm::vec3 rot90 = (dir - pos);
        rot90[1] = 0.0f;
        rot90 = glm::rotateY(rot90, 90.0f);

        rot90 = glm::normalize(rot90);
        dir += rot90;
        pos += rot90;
    }
    if(keyboard->keyDown(SDL_SCANCODE_D))
    {
        glm::vec3 rot90 = (dir - pos);
        rot90[1] = 0.0f;
        rot90 = glm::rotateY(rot90, 90.0f);

        rot90 = glm::normalize(rot90);
        dir -= rot90;
        pos -= rot90;
    }
    if(keyboard->keyDown(SDL_SCANCODE_W))
    {
        glm::vec3 offset = dir - pos;
        offset = glm::normalize(offset);

        dir += offset;
        pos += offset;
    }
    if(keyboard->keyDown(SDL_SCANCODE_S))
    {
        glm::vec3 offset = dir - pos;
        offset = glm::normalize(offset);

        dir -= offset;
        pos -= offset;
    }

    // update the mouse
    if(keyboard->mousePos.x != 0 and keyboard->mousePos.y != 0)
    {
        if(keyboard->mousePos.x != 0)
        {
            glm::vec3 base = dir - pos;
            base = glm::rotateY(base, -1*(keyboard->mousePos.x/10.0f));
            dir = pos + base;
        }
        if(keyboard->mousePos.y != 0)
        {
            glm::vec3 base = dir - pos;
            glm::vec3 axis = glm::rotateY(base, 90.0f);

            axis = glm::normalize(axis);
            glm::vec3 offset = glm::rotate(base, (float)keyboard->mousePos.y/10, axis);
            glm::vec3 adder = offset - base;
            dir += adder;
        }
    }

    return 0;
}

glm::mat4 Camera::getViewMatrix() const
{
    glm::mat4 View = glm::lookAt(
            pos,
            dir,
            glm::vec3(0,1,0)  // Head is up (set to 0,-1,0 to look upside-down)
    );

    return View;
}