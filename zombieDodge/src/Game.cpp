#include <SDL2/SDL.h>
#include "Game.h"

Game* Game::_instance = nullptr;

Game* Game::get_instance(){
    if(!_instance)
        _instance = new Game();

    return _instance;
}

Game::Game(){
    window = nullptr;
}

void Game::Init(){
    if(SDL_Init(SDL_INIT_EVERYTHING)){
        throw SDL_INIT_ERROR;
    }

    //window = SDL_CreateWindow(Config->title,
	window = SDL_CreateWindow("TEST",
            SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED,
            800,
            600,
            SDL_WINDOW_OPENGL
    );
}

void Game::Run(){

}

void Game::Cleanup(){

}
