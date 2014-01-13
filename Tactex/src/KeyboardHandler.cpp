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

KeyboardHandler::KeyboardHandler()
{

}

KeyboardHandler::KeyboardHandler(KeyboardHandler& keyboard)
{

}

void KeyboardHandler::setKey(const SDL_Scancode key)
{
    keyStates[key] = true;
}

bool KeyboardHandler::getKey(const SDL_Scancode key)
{
    return keyStates[key];
}