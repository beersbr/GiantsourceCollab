#include "zombieGame.h"
#include "config.h"

zombieGame* zombieGame::_instance = nullptr;
zombieGame* zombieGame::getInstance() {

        if (!zombieGame::_instance)
            zombieGame::_instance = new zombieGame();

    return zombieGame::_instance;
}

zombieGame::zombieGame() {


}

zombieGame::zombieGame(zombieGame&)
{


}

bool zombieGame::Setup(){

    gameState = SETUP;
    //Initialization flag
    bool success = true;

    gameTimer = SDL_GetTicks();

    //Initialize SDL
    if( SDL_Init( SDL_INIT_EVERYTHING ) < 0 )
    {
        printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
        success = false;
    }
    else
    {
        //Create window
        gameWindow = SDL_CreateWindow(
                WINDOW_CAPTION.c_str(),             // window title
                SDL_WINDOWPOS_CENTERED,     // x position, centered
                SDL_WINDOWPOS_CENTERED,     // y position, centered
                WINDOW_WIDTH,                        // width, in pixels
                WINDOW_HEIGHT,                        // height, in pixels
                SDL_WINDOW_OPENGL           // flags
        );
        if( gameWindow == NULL )
        {
            printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
            success = false;
        }
        else
        {
            //Initialize JPG loading
            int imgFlags = IMG_INIT_JPG;
            if( !( IMG_Init( imgFlags ) & imgFlags ) )
            {
                printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
                success = false;
            }
            else
            {
                //Get window surface
                gameSurface = SDL_GetWindowSurface( gameWindow );
            }
        }

		
    }

    return success;

}

void zombieGame::Run() {
    gameState = SETUP;
	Setup();

	float gameTimer = 0.0f;

	Player* p = new Player();
	SDL_Rect srcRect = {100, 100, 41, 101};	

    while (gameState == RUNNING)
	{
		SDL_BlitSurface(p->image,  NULL, gameSurface, (SDL_Rect*)&srcRect);
		SDL_UpdateWindowSurface( gameWindow );
    }

	delete p;
	p = NULL;

    Cleanup();

}

void zombieGame::Cleanup(){

    gameState = CLEANUP;

}
