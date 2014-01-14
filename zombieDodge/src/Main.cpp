//
//  main.cpp
//  Test Project
//
//  Created by Matt Jacobs on 1/7/14.
//  Copyright (c) 2014 Matt Jacobs. All rights reserved.
//

#include <iostream>
#include "Vector.h"
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include "config.h"
#include <stack>
#include <stdio.h>
#include "gameEngine.h"
#include "GameState.h"
#include "Entity.h"

#include "Player.h"
#include "Enemy.h"
#include <string>

struct StateStruct
{
    void (*StatePointer)();
};

// Global data //
std::stack<StateStruct> gameStates;
gameEngine* gEngine = gameEngine::getInstance();
    int main( int argc, char* args[] )
    {
        gEngine->Setup();

        gEngine->Run();

        gEngine->Cleanup();

        return 0;
    }