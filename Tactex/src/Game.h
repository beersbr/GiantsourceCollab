//
// Created by Brett Beers on 1/12/14.
// Copyright (c) 2014 Brett Beers. All rights reserved.
//

#ifndef __Game_H_
#define __Game_H_

#include <iostream>

#include <OpenGL/gl3.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <OpenGL/glu.h>

#include "KeyboardHandler.h"

class Game {

public:
    static Game* getInstance();

    int setup();
    int run();
    int cleanup();

    ~Game();

private:
    Game();
    Game(Game&);

    static Game* _instance;

    SDL_Window* window;
    SDL_Renderer *renderer;
    SDL_GLContext glContext;
};


#endif //__Game_H_
