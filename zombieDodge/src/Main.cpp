#include <iostream>
<<<<<<< HEAD

#include "Vector.h"

#include <SDL.h>
=======
#include "Vector.h"
#include <SDL2/SDL.h>
>>>>>>> d509675339ce1a7fd0c1b1f716c39fa1d5af1461

// This was taken from a tutorial website as a test. make sure it runs :D

namespace game
{

    class Entity
    {
    public:
        Vector pos;
    };

}

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