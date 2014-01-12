//
// Created by Brett Beers on 1/12/14.
// Copyright (c) 2014 Brett Beers. All rights reserved.
//


#include "Game.h"

Game* Game::getInstance(){
    if(!Game::_instance)
        Game::_instance = new Game();

    return Game::_instance;
}

int Game::setup(){
    if(SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        std::cout << "ERROR SDL_Init" << std::endl;
        return -1;
    }

    window = SDL_CreateWindow(
            "SDL 2 window",             // window title
            SDL_WINDOWPOS_CENTERED,     // x position, centered
            SDL_WINDOWPOS_CENTERED,     // y position, centered
            800,                        // width, in pixels
            600,                        // height, in pixels
            SDL_WINDOW_OPENGL           // flags
    );

    return 0;
}

int Game::run(){
    SDL_Delay(2000);
    return 0;
}

int Game::cleanup(){
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}

Game::~Game(){
    if(window)
        delete window;
    window = nullptr;
}

//******************************************
// Private
//******************************************

// static
Game* Game::_instance = nullptr;

Game::Game(){
    window = nullptr;
}

Game::Game(Game& g){

}


