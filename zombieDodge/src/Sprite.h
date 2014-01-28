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

    void Render(float _x, float _y);

    void SetX(float _x);
    void SetPosition(float _x,float _y);
    void SetY(float _y);

    void SetWidth(int W);
    void SetHeight(int H);

    int GetWidth();
    int GetHeight();

    void SetOrigin(float _x, float _y);
    void PlayAnimation(int begin, int end, int row, float speed);
    void SetUpAnimation(int frameX, int frameY);
    void Rotate(double _a);
    void Flip(char direction);
    SDL_Texture* image;
    SDL_Rect crop;
    SDL_Rect rect;
    double currentAngle = 0;
    float cameraX;
    float cameraY;
    double angle = NULL;
    SDL_RendererFlip flipImage = SDL_FLIP_NONE;
    float posX;
    float posY;
    float originX;
    float originY;

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