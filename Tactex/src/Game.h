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

#include <glm/glm.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "GLCommon.h"
#include "KeyboardHandler.h"
#include "Configurator.h"


class Game {

public:
    static Game* getInstance();

    int setup();
    int run();
    int cleanup();

    ~Game();

public:
    int windowHeight;
    int windowWidth;
    std::map<std::string, std::string>* config;

private:
    Game();
    Game(Game&);

    static Game* _instance;

    SDL_Window* window;
    SDL_Renderer *renderer;
    SDL_GLContext glContext;
};


#endif //__Game_H_
