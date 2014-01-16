//
// Created by Brett Beers on 1/15/14.
// Copyright (c) 2014 Brett Beers. All rights reserved.
//



#ifndef __InputHandler_H_
#define __InputHandler_H_

#include <SDL2/SDL.h>
#include <map>

class InputHandler {
public:
    static InputHandler* getInstance();

    bool keyIsDown(const SDL_Scancode key);

    void keyDown(const SDL_Scancode key);
    void keyUp(const SDL_Scancode key);
private:

    InputHandler();
    InputHandler(InputHandler&);

    static InputHandler* _instance;

    std::map<SDL_Scancode, bool>* keyState;
};


#endif //__InputHandler_H_
