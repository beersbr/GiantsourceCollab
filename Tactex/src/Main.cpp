
#include <iostream>
#include "Game.h"
#include "Configurator.h"

int main(int argc, char * arg[])
{
    Configurator::open("config/game.config");

    Game* game = Game::getInstance();
    game->setup();
    game->run();
    game->cleanup();
    
    return 0;
}