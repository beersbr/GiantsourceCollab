//
//  main.cpp
//  Test Project
//
//  Created by Matt Jacobs on 1/7/14.
//  Copyright (c) 2014 Matt Jacobs. All rights reserved.
//

#include <iostream>
#include "Vector.h"
#include "zombieGame.h"
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include "config.h"
#include <stack>
#include <stdio.h>
//#include "Player.h"
#include "Entity.h"
#include <string>

struct StateStruct
{
    void (*StatePointer)();
};

// Global data //
std::stack<StateStruct> gameStates;

//Starts up SDL and creates window
bool init();

//Updates the main loop
void update();

//Frees media and shuts down SDL
void shutdown();

//The window we'll be rendering to
SDL_Window* gameWindow = NULL;

//The surface contained by the window
SDL_Surface* gameSurface = NULL;

//The image we will load and show on the screen
SDL_Surface* gameBackground = NULL;

SDL_Event		   gameEvent;
int				   gameTimer;
int currentGameState = 0;
int currentLevel = 0;

//Loads Optimized Surface
SDL_Surface* loadOptSurface( std::string path );



SDL_Surface* loadOptSurface( std::string path )
{
    //The final optimized image
    SDL_Surface* optimizedSurface = NULL;

    //Load image at specified path
    SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
    if( loadedSurface == NULL )
    {
        printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
    }
    else
    {
        //Convert surface to screen format
        optimizedSurface = SDL_ConvertSurface( loadedSurface, gameSurface->format, NULL );
        if( optimizedSurface == NULL )
        {
            printf( "Unable to optimize image %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
        }

        //Get rid of old loaded surface
        SDL_FreeSurface( loadedSurface );
    }

    return optimizedSurface;
}

namespace game
{
        bool loadScreen(int screenId)
            {
                //Loading success flag
                bool success = true;

             switch(screenId)

              {
                    case 0:
                         gameBackground = loadOptSurface( "welcome.jpg" );
                         break;

              }


              if(gameBackground == NULL )
                 {
                     printf( "Failed to load  image!\n" );
                     success = false;
                 }   else {

                     success = true;
                 }

                 return success;
        };


    bool loadStateResources(int screenId)
    {
        //Loading success flag
        bool success = true;

        switch(screenId)

        {
            case 0:

                break;

        }


        return success;
    };


    void menuInput() {

        switch( gameEvent.key.keysym.sym ) {

            case SDLK_UP:
                printf( "KEY UP\n" );
                currentGameState = 1;
                break;
            case SDLK_DOWN:
                printf( "KEY DOWN\n" );
                break;

        }

    };

    void gameInput() {

        switch( gameEvent.key.keysym.sym ) {

            case SDLK_UP:
                printf( "KEY UP\n" );
                break;
            case SDLK_DOWN:
                printf( "KEY DOWN\n" );
                break;

        }

    };

    class Entity
    {



    public:
        Vector pos;

    };




}

bool init()
{
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

void update(){

    if ( (SDL_GetTicks() - gameTimer) >= FRAME_RATE )
    {

        //Apply the image
        SDL_BlitSurface( gameBackground, NULL, gameSurface, NULL );

        //Update the surface
        SDL_UpdateWindowSurface( gameWindow );

        switch(currentGameState) {


            case -1:
                //Load the Welcome screen
                game::loadStateResources(currentGameState);
                break;

            case 0:
                //Load the Welcome screen
                game::loadScreen(currentGameState);
                game::menuInput();
                break;

            case 1:
                //Load the Welcome screen


                //Player::update();
                game::gameInput();
                break;



        }


        gameTimer = SDL_GetTicks();
    }



}

void shutdown() {

    SDL_FreeSurface( gameBackground );
    gameBackground = NULL;

    //Destroy window
    SDL_DestroyWindow( gameWindow );
    gameWindow = NULL;

    // Tell SDL to shutdown and free any resources it was using. //
    SDL_Quit();

}

int main( int argc, char* args[] )
{


    //Start up SDL and create window
    if( !init() )
    {
        printf( "Failed to initialize!\n" );
    }
    else
    {

            //Main loop flag
            bool quit = false;


            //While application is running
            while( !quit )
            {
                //Handle events on queue
                while( SDL_PollEvent( &gameEvent ) != 0 )
                {
                    //User requests quit
                    if( gameEvent.type == SDL_QUIT )
                    {
                        quit = true;
                    } //User presses a key
                    else {

                    }
                }



                    update();
        }
    }

    //Free resources and close SDL
    shutdown();

    return 0;
}



