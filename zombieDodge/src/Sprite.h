#ifndef __SPRITE_H_
#define __SPRITE_H_
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include "Vector.h"
class Sprite
{
public:
    Sprite(SDL_Renderer* renderer, std::string FilePath, float _x, float _y, int w, int h, float _cameraX, float _cameraY);
    Sprite(std::string FilePath, float _x, float _y, int w, int h);
    ~Sprite();


    void Draw(float _x, float _y);

    void SetX(float _x);
    void SetY(float _y);
    //void SetPosition(float _x, float _y);
     /*
    float GetX();
    float GetY();
       */
    void SetWidth(int W);
    void SetHeight(int H);
    int GetWidth();
    int GetHeight();

    void SetOrigin(float _x, float _y);
    void PlayAnimation(int begin, int end, int row, float speed, SDL_Rect clip,int imgWidth, int imgHeight);
    void SetUpAnimation(int frameX, int frameY);
    SDL_Texture* image;
    SDL_Rect crop;
    //Vector* position;
    //Vector* camera;
    float posX;
    float posY;
    float originX;
    float originY;



    SDL_Rect rect;



    int imgWidth;
    int imgHeight;
    int currentFrame;
    int animationDelay;

    int frameX;
    int frameY;

    SDL_Renderer* renderer;
private:


};

#endif