//
//  main.cpp
//  Test Project
//
//  Created by Matt Jacobs on 1/7/14.
//  Copyright (c) 2014 Matt Jacobs. All rights reserved.
//

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <stack>
#include <string>
#include <stdio.h>

//ENGINE FILES

#include "gameEngine.h"


struct StateStruct
{
    void (*StatePointer)();
};

// Global data //
std::stack<StateStruct> gameStates;


int main( int argc, char* args[] )
{

    gameEngine* gEngine = gameEngine::getInstance();

        if (gEngine->Setup()) {

            gEngine->Run();

        }
        return 0;
}