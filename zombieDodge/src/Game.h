#ifndef __Game_H_
#define __Game_H_

#include <SDL2/SDL.h>

#include <iostream>

enum GAME_ERROR {
    SDL_INIT_ERROR
};

class Game
{
public:
    static Game* get_instance();

    void Init();
    void Run();
    void Cleanup();

private:
    Game();
    Game(Game& g);
    ~Game();

    static Game* _instance;

    SDL_Window* window;

};

#endif // __Game_H_