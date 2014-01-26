//
//  main.cpp
//  Test Project
//
//  Created by Matt Jacobs on 1/7/14.
//  Copyright (c) 2014 Matt Jacobs. All rights reserved.
//

//ENGINE FILES
#include <iostream>
#include "gameEngine.h"
#include "Configurator.h"


int main( int argc, char* args[] )
{

        gameEngine* gEngine = gameEngine::getInstance();
        //Configurator::open("config/game.config");


        if (gEngine->Setup()) {

            gEngine->Run();

        } else {
            printf("FAILed setup");

        }
        return 0;
}