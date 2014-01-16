//
//  main.cpp
//  Test Project
//
//  Created by Matt Jacobs on 1/7/14.
//  Copyright (c) 2014 Matt Jacobs. All rights reserved.
//



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