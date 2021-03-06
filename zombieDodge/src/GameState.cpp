#include "GameState.h"


GameState::GameState(int _stateId, std::string _name, int _key) {

           stateId = _stateId;
           name = _name;
           key = _key;

}

bool GameState::Setup(){



    //Initialization flag
    bool success = true;

    return success;

}

bool GameState::LoadResources()
{
    //Loading success flag
    bool success = true;

    return success;
};


void GameState::HandleInput(SDL_Event& event) {

    gameEngine* engine = gameEngine::getInstance();

    if( event.type == SDL_KEYDOWN ) {
            std::cout << "CODE = " <<  event.key.keysym.sym << std::endl;
            //Select surfaces based on key press
            switch( event.key.keysym.sym ) {
                case SDLK_ESCAPE:
                    printf( "ESCAPE\n" );

                    engine->SetGameState(CLEANUP);

                    break;
                case SDLK_UP:
                    printf( "KEY UP Menu\n" );
                    //this->currentGameState = 1;
                    break;
                case SDLK_DOWN:
                    printf( "KEY DOWN Menu\n" );
                    break;
            }
        }

};