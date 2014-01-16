#ifndef  __ENGINE_H
#define __ENGINE_H

#include <iostream>
#include <stack>
#include <string>
#include <stdio.h>
#include <iosfwd>
#include <assert.h>
#include <math.h>
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>

#include "InputHandler.h"
#include "config.h"
#include "common.h"
#include "GameState.h"
#include "Vector.h"
#include "Entity.h"
#include "Player.h"
#include "Enemy.h"


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


    float gameTimer;
    Player* currentPlayer = nullptr;
    Enemy* currentEnemy = nullptr;
    int gameState=0;
    int playerCnt =0;
    int enemyCnt = 0;

    //-----------Main Functions
    bool Setup();
    void Run();
    bool GameInit();
    void Update();
    void Draw();
    void Cleanup();

     //----------Interface Functions
    void SetPlayer(std::string playerId);
    float getTimer();
    void SetGameState(int state);

    //-----------Input Functions
    void MenuInput();
    void GameInput();

    //-----------Graphics Functions

    //SDL_Window* getWindow();
    SDL_Surface* getGameSurface();
    SDL_Texture* getBackground();
    //SDL_Renderer* getRender();

    //The window we'll be rendering to
    SDL_Window* gameWindow;

    SDL_Texture* PlayerImage;

    //The surface contained by the window
    SDL_Surface* gameSurface;

    //The image we will load and show on the screen
    SDL_Texture* gameBackground;

    //SDL_Surface* gameBackground;

    SDL_Renderer* gameRender;

    SDL_Surface* LoadImage(const std::string path);
    static SDL_Texture* LoadTexture(const std::string &file, SDL_Renderer *ren);
    SDL_Texture* LoadTexture(const std::string &file);
    void logSDLError(std::ostream &os, const std::string &msg);
    void RenderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y, int w, int h);
    void RenderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y);
    void RenderTexture(SDL_Texture *tex, int x, int y);
    bool LoadScreen();
    bool loadStateResources(int screenId);
    int totalEnemyCnt = 0;
    std::map<int, Enemy*> enemies;

    void ApplySurface(float x, float y, SDL_Texture *source, SDL_Renderer *destination);



private:
    gameEngine();

    gameEngine(gameEngine&);

    static gameEngine* _instance;



};
#endif