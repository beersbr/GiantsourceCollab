#ifndef __SPRITE_H_
#define __SPRITE_H_
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
class Sprite
{
public:
    Sprite(SDL_Renderer* passed_renderer, std::string FilePath, int x, int y, int w, int h, float *passed_CameraX, float *passed_CameraY);
    Sprite(std::string FilePath, int x, int y, int w, int h);
    ~Sprite();

    void DrawSteady();
    void Draw();

    void SetX(float X);
    void SetY(float Y);
    void SetPosition(float X, float Y);

    float GetX();
    float GetY();

    void SetWidth(int W);
    void SetHeight(int H);
    int GetWidth();
    int GetHeight();

    void SetOrigin(float X, float Y);
    void PlayAnimation(int BeginFrame, int EndFrame, int Row, float Speed);
    void SetUpAnimation(int passed_Amount_X, int passed_Amount_Y);
private:
    float *cameraX;
    float *cameraY;

    float originX;
    float originY;

    float xPos;
    float yPos;

    SDL_Texture* image;
    SDL_Rect rect;

    SDL_Rect crop;

    int imgWidth;
    int imgHeight;
    int currentFrame;
    int animationDelay;

    int frameX;
    int frameY;

    SDL_Renderer* renderer;
};

#endif