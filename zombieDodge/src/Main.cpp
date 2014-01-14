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
#include "config.h"
#include "gameEngine.h"
#include "GameState.h"
#include "Vector.h"
#include "Entity.h"
#include "Player.h"
#include "Enemy.h"

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