#include "Sprite.h"
#include "gameEngine.h"
Sprite::Sprite(SDL_Renderer* render,std::string path, float _x, float _y, int w, int h, float _cameraX, float _cameraY)
{

    image = NULL;

    image =  gameEngine::getInstance()->LoadTexture(path.c_str());
    renderer = render;

    if ( image == NULL)
    {
        std::cout << "Couldn't Load " << path.c_str() << std::endl;
    }

    SDL_QueryTexture(image,NULL,NULL, &imgWidth, &imgHeight);
    crop.x = 0;
    crop.y = 0;
    crop.w = w;
    crop.h = h;

    posX = _x;
    posY = _y;
    originX = 0;
    originY = 0;
    currentFrame = 0;
    frameX = 0;
    frameY = 0;


}

void Sprite::Rotate(double _a) {

       angle = _a;


}

void Sprite::Flip(char _a) {

    switch(_a) {

        case 'h':
            flipImage = SDL_FLIP_HORIZONTAL;
            break;
        case 'v':
            flipImage = SDL_FLIP_VERTICAL;

        default:
            flipImage = SDL_FLIP_NONE;


    }

}

Sprite::Sprite(std::string path,float _x, float _y, int w, int h)
{

    Sprite(gameEngine::getInstance()->gameRender, path, _x, _y, w, h, 0,0);
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
        if (end <= this->currentFrame)
            this->currentFrame = begin;
        else
            this->currentFrame++;

        crop.x = currentFrame * (imgWidth/frameX);
        crop.y = (row-1) * (imgHeight/frameY);
        crop.w = imgWidth/frameX;
        crop.h = imgHeight/frameY;


        animationDelay = SDL_GetTicks();
    }
}

void Sprite::Render(float _x, float _y)
{



        SDL_Rect box;
        box.x = posX;
        box.y = posY;
        box.w = crop.w;
        box.h = crop.h;

        //Render to screen
        SDL_RenderCopyEx(renderer,image, &crop, &box, angle, NULL, flipImage );



    //SDL_RenderCopy(renderer,image, &crop, &box);

}

void Sprite::SetX(float _x)
{
    posX = _x;

    rect.x = static_cast<int>(posX - originX);
}

void Sprite::SetY(float _y)
{
    posY = _y;

    rect.y = static_cast<int>(posY - originY);
}
 /*
void Sprite::SetPosition(float _x, float _y)
{    std::cout << "SET POSITION -> = x=" << _x << "Y = " << _y << std::endl;
    position->x = _x - originX;
    position->y = _y - originY;

    //rect.x =static_cast<int>(position->x - originX);
    //rect.y = static_cast<int>(position->y - originY);
}
*/

void Sprite::SetOrigin(float _x, float _y)
{

    //std::cout << "SET ORIGIN -> VEL = x=" << _x << "Y = " << _y << std::endl;
    originX = _x;
    originY = _y;
    //std::cout << "SET POSITION NOW -> VEL = x=" << _x << "Y = " << _y << std::endl;
    //std::cout << "SET POSITION SET with X = " << position->x << std::endl;
    //Vector* pos = GetPosition();
    //float xPosi = GetX();
    //std::cout << "SET POSITION xPosi -> x=" << pos->x << std::endl;
    //SetPosition(position->x, position->y);
    //position->x -= originX;
    //position->y -= originY;
    //std::cout << "SET POSITION SET" << std::endl;
}


void Sprite::SetPosition(float _x, float _y) {

    posX = _x;
    posY = _y;

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

Sprite::~Sprite() {

    SDL_DestroyTexture(image);

}