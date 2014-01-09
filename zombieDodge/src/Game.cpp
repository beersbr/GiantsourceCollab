#include <SDL2/SDL.h>
#include "Game.h"
#include "config.h"

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

    window = SDL_CreateWindow(WINDOW_CAPTION.c_str(),
            SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED,
            WINDOW_WIDTH,
            WINDOW_HEIGHT,
            SDL_WINDOW_OPENGL
    );
}

void Game::Run(){

}

void Game::Cleanup(){

}
