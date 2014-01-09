#include <iostream>

#include <SDL.h>

// This was taken from a tutorial website as a test. make sure it runs :D

int main(int argc, char * arg[])
{
    // init SDL
    if(SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        std::cout << "ERROR SDL_Init" << std::endl;
        
        return -1;
    }
    
    // create a window
    SDL_Window * window = SDL_CreateWindow(
                                           "SDL 2 window",             // window title
                                           SDL_WINDOWPOS_CENTERED,     // x position, centered
                                           SDL_WINDOWPOS_CENTERED,     // y position, centered
                                           640,                        // width, in pixels
                                           480,                        // height, in pixels
                                           SDL_WINDOW_OPENGL           // flags
                                           );
    
    // wait 5 secs
    SDL_Delay(5000);
    
    // clean up
    SDL_DestroyWindow(window);
    SDL_Quit();
    
    return 0;
}