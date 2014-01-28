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
#include <SDL2_ttf/SDL_ttf.h>
#include "Jsonator.h"
#include "Configurator.h"
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
    int gameState=0;
    float gameStart = 0;
    int playerCnt =0;
    int enemyCnt = 0;
    int followEnemyCnt = 0;
    SDL_Rect camera;
    std::map<std::string, std::string>* config;
    //Globally used font
    bool godMode = false;

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
    bool LoadText( std::string textureText, SDL_Color textColor );
    void SetColor(SDL_Texture *texture, Uint8 red, Uint8 green, Uint8 blue );

    void SetBlendMode(SDL_Texture *texture, SDL_BlendMode blending );

    void SetAlpha(SDL_Texture *texture, Uint8 alpha );
    //-----------Input Functions
    void MenuInput();
    void GameInput();

    int enemySpawnRate = 15;
    double spawnThreshold = .40;
    //-----------Graphics Functions

    //SDL_Window* getWindow();
    SDL_Surface* getGameSurface();
    SDL_Texture* getBackground();
    //SDL_Renderer* getRender();
    SDL_Color textColor;
    //The window we'll be rendering to
    SDL_Window* gameWindow;
     int textWidth;
    int textHeight;
    SDL_Texture* gameText;

    //The surface contained by the window
    SDL_Surface* gameSurface;

    //The image we will load and show on the screen
    SDL_Texture* gameBackground;

    SDL_Texture* gameHUD;

    Jsonator *gameConfig;

    TTF_Font *gameFont = NULL;

    int levelWidth = 1600;
    int levelHeight = 1131;
    //SDL_Surface* gameBackground;
    int mouseX;
    int mouseY;
    int windowWidth, windowHeight;
    SDL_Renderer* gameRender;

    SDL_Surface* LoadImage(const std::string path);
    SDL_Texture* LoadTexture(const std::string &file);
    void RenderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y, int w, int h);
    void RenderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y);
    void Render(SDL_Texture *texture, int x, int y, int h, int w, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip );
    bool LoadScreen();
    bool loadStateResources(int screenId);
    int totalEnemyCnt = 0;
    std::vector<Bullet*> bullets;
    std::vector<Enemy*> enemies;
    void addBullet(Bullet* b);


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