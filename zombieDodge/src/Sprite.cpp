#include "Sprite.h"
#include "gameEngine.h"
Sprite::Sprite(SDL_Renderer* render,std::string path, int x, int y, int w, int h, float *_cameraX, float *_cameraY)
{


    cameraX = _cameraX;
    cameraY = _cameraY;

    renderer = render;
    image = NULL;
    image = IMG_LoadTexture(renderer,path.c_str());

    if (image == NULL)
    {
        std::cout << "Couldn't Load " << path.c_str() << std::endl;
    }

    rect.x = x;
    rect.y = y;
    rect.w = w;
    rect.h = h;

    SDL_QueryTexture(image,NULL,NULL, &imgWidth, &imgHeight);

    crop.x = 0;
    crop.y = 0;
    crop.w = imgWidth;
    crop.h = imgHeight;

    xPos = x;
    yPos = y;

    originX = 0;
    originY = 0;

    currentFrame = 0;
    frameX = 0;
    frameY = 0;
}

Sprite::Sprite(std::string path, int x, int y, int w, int h)
{

    *cameraX = 0;
    *cameraX = 0;

    renderer = gameEngine::getInstance()->gameRender;

    Sprite(renderer, path, x, y, w, h, cameraX, cameraY);
}

void Sprite::SetUpAnimation(int _frameX, int _frameY)
{
    frameX = _frameX;
    frameY = _frameY;
}

void Sprite::PlayAnimation(int begin, int end, int row, float speed)
{
    if (animationDelay+speed < SDL_GetTicks())
    {

        if (end <= currentFrame)
            currentFrame = begin;
        else
            currentFrame++;

        crop.x = currentFrame * (imgWidth/frameX);
        crop.y = row * (imgHeight/frameY);
        crop.w = imgWidth/frameX;
        crop.h = imgHeight/frameY;

        animationDelay = SDL_GetTicks();
    }
}

void Sprite::DrawSteady()
{
    SDL_RenderCopy(renderer,image, &crop, &rect);
}

void Sprite::Draw()
{
    SDL_Rect position;
    position.x = rect.x + *cameraX;
    position.y = rect.y + *cameraY;
    position.w = rect.w;
    position.h = rect.h;

    SDL_RenderCopy(renderer,image, &crop, &position);


}

void Sprite::SetX(float X)
{
    xPos = X;

    rect.x = int(xPos - originX);
}

void Sprite::SetY(float Y)
{
    yPos = Y;

    rect.y = int(yPos - originY);
}

void Sprite::SetPosition(float X, float Y)
{
    xPos = X;
    yPos = Y;

    rect.x = int(xPos - originX);
    rect.y = int(yPos - originY);
}

float Sprite::GetX()
{
    return xPos;
}

float Sprite::GetY()
{
    return yPos;
}

void Sprite::SetOrigin(float X, float Y)
{
    originX = X;
    originY = Y;

    SetPosition(GetX(), GetY());

}

void Sprite::SetWidth(int W)
{
    rect.w = W;
}

void Sprite::SetHeight(int H)
{
    rect.h = H;
}

int Sprite::GetWidth()
{
    return rect.w;
}

int Sprite::GetHeight()
{
    return rect.h;
}