//
// Created by Brett Beers on 1/15/14.
// Copyright (c) 2014 Brett Beers. All rights reserved.
//


#include "InputHandler.h"

InputHandler* InputHandler::_instance = nullptr;

InputHandler* InputHandler::getInstance()
{
    if(!InputHandler::_instance)
        InputHandler::_instance = new InputHandler();

    return InputHandler::_instance;
}

InputHandler::InputHandler()
{
    keyState = new std::map<SDL_Scancode, bool>();
}

InputHandler::InputHandler(InputHandler& inputHandler)
{

}

bool InputHandler::keyIsDown(const SDL_Scancode key)
{
    return (*keyState)[key];
}

void InputHandler::keyDown(const SDL_Scancode key)
{
    (*keyState)[key] = true;
}

void InputHandler::keyUp(const SDL_Scancode key)
{
    (*keyState)[key] = false;
}
