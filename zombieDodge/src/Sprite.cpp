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
    image = NULL;
    printf( "LOAD TEXTURE\n" );
    image =  gameEngine::getInstance()->LoadTexture(path.c_str());

    if ( image == NULL)
    {
        std::cout << "Couldn't Load " << path.c_str() << std::endl;
    }


    printf( "QUERY TEXTURE\n" );

     //SDL_Rect rect;
    rect.x = static_cast<int>(_x);
    rect.y = static_cast<int>(_y);
    rect.w = w;
    rect.h = h;

    SDL_QueryTexture(image,NULL,NULL, &imgWidth, &imgHeight);

    crop.x = 0;
    crop.y = 0;
    crop.w = w;
    crop.h = h;
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

void Sprite::PlayAnimation(int begin, int end, int row, float speed,SDL_Rect clip,int imgWidth, int imgHeight)
{

    std::cout << "animationDelay" << animationDelay << std::endl;
    std::cout << "ticks" << SDL_GetTicks() << std::endl;
   // if (animationDelay+speed < SDL_GetTicks())
    //{

        if (end <= this->currentFrame)
            this->currentFrame = begin;
        else
            this->currentFrame++;
        /*
        std::cout << "CURRENT FRAME X -==" << this->frameX << std::endl;
        std::cout << "CURRENT IMAGE WIDTH  -==" << imgWidth << std::endl;
        std::cout << "PLAY ANIMATION WITH PRERENDER IMAGE clip x" << clip.x << std::endl;
        std::cout << "PLAY ANIMATION WITHRENDER IMAGE clip y" << clip.y << std::endl;
        std::cout << "PLAY ANIMATION WITHRENDER IMAGE clip w" << clip.w << std::endl;
        std::cout << "PLAY ANIMATION WITHRENDER IMAGE clip h" << clip.h << std::endl;

        std::cout << "------------"  << std::endl;
        std::cout << "------------" << std::endl;
        */
        crop.x = currentFrame * (imgWidth/frameX);
        crop.y = (row-1) * (imgHeight/frameY);
        crop.w = imgWidth/frameX;
        crop.h = imgHeight/frameY;
        std::cout << "PLAY ANIMATION WITH RENDER IMAGE CROP x" << crop.x << std::endl;
        std::cout << "PLAY ANIMATION WITHRENDER IMAGE CROP y" << crop.y << std::endl;
        std::cout << "PLAY ANIMATION WITHRENDER IMAGE CROP w" << crop.w << std::endl;
        std::cout << "PLAY ANIMATION WITHRENDER IMAGE CROP h" << crop.h << std::endl;

        //animationDelay = SDL_GetTicks();
    //}
}

void Sprite::Draw(float _x, float _y)
{

    //Vector* posi = this->position;
     /*
    std::cout << "xPosi at draw sprite -> x=" << _x << std::endl;
    SDL_Rect box;
    box.x = static_cast<int>(_x);
    box.y = static_cast<int>(_y);
    box.w = crop.w;
    box.h = crop.h;
     */

    gameEngine::getInstance()->RenderTexture(image, _x, _y,crop.w,crop.h,crop);
      /*

    //crop.x = 0;
    //crop.y = 0;
    SDL_Rect clip;

    clip.x = crop.x;
    clip.y = crop.y;
    clip.h = crop.h;
    clip.w = crop.w;

    std::cout << "RENDER IMAGE TO SCREEN --- " << std::endl;
    std::cout << "RENDER IMAGE CROP x" << crop.x << std::endl;
    std::cout << "RENDER IMAGE CROP y" << crop.y << std::endl;
    std::cout << "RENDER IMAGE CROP w" << crop.w << std::endl;
    std::cout << "RENDER IMAGE CROP h" << crop.h << std::endl;
    gameEngine::getInstance()->RenderTexture(image, _x, _y,crop.w,crop.h,clip);

    //SDL_RenderCopy(renderer,image, &clip, &box);
    */
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