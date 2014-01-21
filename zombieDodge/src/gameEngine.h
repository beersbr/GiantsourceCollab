#ifndef  __ENGINE_H
#define __ENGINE_H

#include <iostream>
#include <stack>
#include <string>
#include <vector>
#include <stdio.h>
#include <iosfwd>
#include <assert.h>
#include <math.h>
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <SDL2_mixer/SDL_mixer.h>
#include "InputHandler.h"
#include "config.h"
#include "common.h"
#include "GameState.h"
#include "Vector.h"
#include "Entity.h"
#include "Sprite.h"
#include "Bullet.h"
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

    bool gameReady = false;


    float gameTimer;
    Player* currentPlayer = nullptr;
    Enemy* currentEnemy = nullptr;
    int gameState=0;
    int playerCnt =0;
    int enemyCnt = 0;
    int followEnemyCnt = 0;

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


    float CameraX;
    float CameraY;

    SDL_Surface* LoadImage(const std::string path);
    static SDL_Texture* LoadTexture(const std::string &file, SDL_Renderer *ren);
    SDL_Texture* LoadTexture(const std::string &file);
    static Vector getPlayerPos();
    void logSDLError(std::ostream &os, const std::string &msg);
    void RenderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y, int w, int h);
    void RenderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y);
    void RenderTexture(SDL_Texture *tex, int x, int y);
    void RenderTexture(SDL_Texture *tex, int x, int y, int w, int h);
    void RenderTexture(SDL_Texture *tex, int x, int y, int w, int h, SDL_Rect clip);
    bool LoadScreen();
    bool loadStateResources(int screenId);
    int totalEnemyCnt = 0;
    //std::map<int, Enemy*> enemies;
    //std::map<int, Bullet*> bullets;
    std::vector<Bullet*> bullets;
    std::vector<Enemy*> enemies;
    void ApplySurface(float x, float y, SDL_Texture *source, SDL_Renderer *destination);

    bool CheckCollision( SDL_Rect A, SDL_Rect B )
    {
        //The sides of the rectangles
        int leftA, leftB;
        int rightA, rightB;
        int topA, topB;
        int bottomA, bottomB;

        //Calculate the sides of rect A
        leftA = A.x;
        rightA = A.x + A.w;
        topA = A.y;
        bottomA = A.y + A.h;

        //Calculate the sides of rect B
        leftB = B.x;
        rightB = B.x + B.w;
        topB = B.y;
        bottomB = B.y + B.h;

        //If any of the sides from A are outside of B
        if( bottomA <= topB )
        {
            return false;
        }

        if( topA >= bottomB )
        {
            return false;
        }

        if( rightA <= leftB )
        {
            return false;
        }

        if( leftA >= rightB )
        {
            return false;
        }

        //If none of the sides from A are outside B
        return true;
    }


private:
    gameEngine();

    gameEngine(gameEngine&);

    static gameEngine* _instance;



};
#endif