//
// Created by Brett Beers on 1/12/14.
// Copyright (c) 2014 Brett Beers. All rights reserved.
//

#ifndef __Controller_H_
#define __Controller_H_

#include <map>
#include <SDL2/SDL.h>

class KeyboardHandler {
public:
    static KeyboardHandler * getInstance();

    void setKey(const SDL_Scancode key);
    bool getKey(const SDL_Scancode key);

private:
    KeyboardHandler();
    KeyboardHandler(KeyboardHandler & );

    static KeyboardHandler * _instance;

    std::map<SDL_Scancode, bool> keyStates;

};


#endif //__Controller_H_
