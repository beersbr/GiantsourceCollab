#include "Sprite.h"
#include "gameEngine.h"
Sprite::Sprite(SDL_Renderer* render,std::string path, float _x, float _y, int w, int h, float _cameraX, float _cameraY)
{

    //camera = new Vector(_cameraX,_cameraY,0);
    printf( "CREATE POSITION\n" );
    currentFrame = 1;
   // this->position = new Vector();
    //this->position->x = _x;
    //this->position->y = _y;
    posX = _x;
    posY = _y;

    //renderer = render;
    this->image = NULL;
    printf( "LOAD TEXTURE\n" );
    this->image = IMG_LoadTexture(render,path.c_str());

    if ( this->image == NULL)
    {
        std::cout << "Couldn't Load " << path.c_str() << std::endl;
    }


    printf( "QUERY TEXTURE\n" );


    //rect.x = x;
    //rect.y = y;
    rect.w = w;
    rect.h = h;

    SDL_QueryTexture(image,NULL,NULL, &imgWidth, &imgHeight);
    imgHeight = imgHeight;
    imgWidth = imgWidth;
    crop.x = 0;
    crop.y = 0;
    crop.w = imgWidth;
    crop.h = imgHeight;
    std::cout << "RENDER IMAGE CROP x" <<  crop.x << std::endl;
    std::cout << "RENDER IMAGE CROP y" <<  crop.y << std::endl;
    std::cout << "RENDER IMAGE CROP w" <<  crop.w << std::endl;
    std::cout << "RENDER IMAGE CROP h" <<  crop.h << std::endl;
   // printf( "SET POSITION\n" );
    //position = new Vector(pos->x,pos->y,pos->z);
    //position->x = pos.x;
    //position->y = pos.y;


    //Vector* tempVector = new Vector();

    std::cout << "SET POSITION xPosi -> x=" << posX << std::endl;

    printf( "SET ORIGIN\n" );
    originX = 0;
    originY = 0;
    printf( "SET CURRENT FRAME\n" );
    currentFrame = 0;
    frameX = 0;
    frameY = 0;

    printf( "GO SET UP ANIMATION\n" );

}

Sprite::Sprite(std::string path,float _x, float _y, int w, int h)
{

    printf( "SET RENDER \n" );
    renderer = gameEngine::getInstance()->gameRender;
    printf( "CREATE SPRITE AGAIN \n" );

    Sprite(renderer, path, _x, _y, w, h, 0,0);
}

void Sprite::SetUpAnimation(int _frameX, int _frameY)
{
    frameX = _frameX;
    frameY = _frameY;
}

void Sprite::PlayAnimation(int begin, int end, int row, float speed)
{

    //std::cout << "animationDelay" << animationDelay << std::endl;
    //std::cout << "ticks" << SDL_GetTicks() << std::endl;
    if (animationDelay+speed < SDL_GetTicks())
    {

        if (end <= this->currentFrame)
            this->currentFrame = begin;
        else
            this->currentFrame++;

        std::cout << "CURRENT FRAME X -==" << this->frameX << std::endl;
        std::cout << "CURRENT IMAGE WIDTH  -==" << this->imgWidth << std::endl;
        std::cout << "PLAY ANIMATION WITH PRERENDER IMAGE CROP x" << this->crop.x << std::endl;
        std::cout << "PLAY ANIMATION WITHRENDER IMAGE CROP y" << this->crop.y << std::endl;
        std::cout << "PLAY ANIMATION WITHRENDER IMAGE CROP w" << this->crop.w << std::endl;
        std::cout << "PLAY ANIMATION WITHRENDER IMAGE CROP h" << this->crop.h << std::endl;

        std::cout << "------------" << crop.h << std::endl;
        std::cout << "------------" << crop.h << std::endl;
        this->crop.x = this->currentFrame * (this->imgWidth/this->frameX);
        this->crop.y = row * (this->imgHeight/this->frameY);
        this->crop.w = this->imgWidth/this->frameX;
        this->crop.h = this->imgHeight/this->frameY;
        std::cout << "PLAY ANIMATION WITH RENDER IMAGE CROP x" << this->crop.x << std::endl;
        std::cout << "PLAY ANIMATION WITHRENDER IMAGE CROP y" << this->crop.y << std::endl;
        std::cout << "PLAY ANIMATION WITHRENDER IMAGE CROP x" << this->crop.w << std::endl;
        std::cout << "PLAY ANIMATION WITHRENDER IMAGE CROP y" << this->crop.h << std::endl;

        animationDelay = SDL_GetTicks();
    }
}

void Sprite::DrawSteady()
{
    SDL_RenderCopy(renderer,image, &crop, &rect);
}

void Sprite::Draw(SDL_Renderer *renderer, float _x, float _y)
{
    SDL_Rect box;
    //Vector* posi = this->position;

    std::cout << "xPosi -> x=" << _x << std::endl;
    box.x = _x;
    box.y = _y;
    box.w = rect.w;
    box.h = rect.h;

    //crop.x = 0;
    //crop.y = 0;

    std::cout << "RENDER IMAGE TO SCREEN --- " << std::endl;
    std::cout << "RENDER IMAGE CROP x" << crop.x << std::endl;
    std::cout << "RENDER IMAGE CROP y" << crop.y << std::endl;
    std::cout << "RENDER IMAGE CROP x" << crop.w << std::endl;
    std::cout << "RENDER IMAGE CROP y" << crop.h << std::endl;

    SDL_RenderCopy(renderer,image, &crop, &box);
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

    std::cout << "SET ORIGIN -> VEL = x=" << _x << "Y = " << _y << std::endl;
    originX = _x;
    originY = _y;
    std::cout << "SET POSITION NOW -> VEL = x=" << _x << "Y = " << _y << std::endl;
    //std::cout << "SET POSITION SET with X = " << position->x << std::endl;
    //Vector* pos = GetPosition();
    //float xPosi = GetX();
    //std::cout << "SET POSITION xPosi -> x=" << pos->x << std::endl;
    //SetPosition(position->x, position->y);
    //position->x -= originX;
    //position->y -= originY;
    std::cout << "SET POSITION SET" << std::endl;
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