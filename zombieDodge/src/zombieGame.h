#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>

#include "Player.h"

 enum GAMESTATES {

     SETUP = 100,
     RUNNING= 100,
     CLEANUP = 200,
     ERROR = -100

 };

class zombieGame {

public:
    static zombieGame* getInstance();

    bool Setup();
    void Run();
    void Cleanup();


private:
    zombieGame();
    zombieGame(zombieGame&);

    static zombieGame* _instance;
    int gameState;
    int gameTimer;


    SDL_Window* gameWindow;
    SDL_Surface* gameSurface;

};
