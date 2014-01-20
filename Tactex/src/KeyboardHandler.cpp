//
// Created by Brett Beers on 1/12/14.
// Copyright (c) 2014 Brett Beers. All rights reserved.
//


#include "KeyboardHandler.h"

KeyboardHandler *KeyboardHandler::_instance = nullptr;

KeyboardHandler *KeyboardHandler::getInstance()
{
    if(!KeyboardHandler::_instance)
        KeyboardHandler::_instance = new KeyboardHandler();

    return KeyboardHandler::_instance;
}

void KeyboardHandler::update(SDL_Event& e)
{
    switch(e.type)
    {
        case SDL_KEYUP:
        {
            onKeyUp(e.key.keysym.scancode);
            break;
        }
        case SDL_KEYDOWN:
        {
            onKeyDown(e.key.keysym.scancode);
            break;
        }
    }
}

void KeyboardHandler::updateMouse()
{
    SDL_GetRelativeMouseState(&mousePos.x,&mousePos.y);
}


bool KeyboardHandler::keyDown(const SDL_Scancode key)
{
    return keyStates[key];
}

KeyboardHandler::KeyboardHandler()
{

}

KeyboardHandler::KeyboardHandler(KeyboardHandler& keyboard)
{

}

void KeyboardHandler::onKeyUp(const SDL_Scancode key)
{
    keyStates[key] = false;
}

void KeyboardHandler::onKeyDown(const SDL_Scancode key)
{
    keyStates[key] = true;
}

