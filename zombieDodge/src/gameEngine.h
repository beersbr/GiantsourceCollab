#ifndef  ENGINE_H
#define ENGINE_H


#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include "Player.h"

enum GAMESTATES {

    SETUP = 1,
    MENU = 50,
    PLAYING = 100,
    GAME_OVER=200,
    EXIT = 300,
    CLEANUP = 500,
    ERROR = -1

};

class gameEngine {

public:
    static gameEngine* getInstance();
    SDL_Event getEvent();
    bool gameReady = false;
    SDL_Window* getWindow();
    SDL_Surface* getGameSurface();
    SDL_Surface* getBackground();
    float getTimer();
    float gameTimer;
    Player* currentPlayer = nullptr;
    int gameState=0;
    int currentLevel = 0;
    bool Setup();
    void Run();
    void Draw();
    void Update(SDL_Event &event);
    void Cleanup();
    void SetPlayer(std::string playerId);
    bool loadScreen(int screenId);
    bool loadStateResources(int screenId);
    void menuInput(SDL_Event &event);
    void gameInput(SDL_Event &event);
    SDL_Surface* LoadImage(const std::string& path);
    void ApplySurface( int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip = NULL );

    void SetGameState(int state);
    bool GameInit();
    //Loads Optimized Surface




private:
    gameEngine();

    gameEngine(gameEngine&);

    static gameEngine* _instance;

    //The window we'll be rendering to
    SDL_Window* gameWindow;

    //The surface contained by the window
    SDL_Surface* gameSurface;

    //The image we will load and show on the screen
    SDL_Surface* gameBackground;



    int currentGameState = 0;




};
#endif