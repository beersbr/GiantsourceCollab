#include "Bullet.h"
#include "gameEngine.h"


Bullet::Bullet(float _x, float _y, float _z)
{

    vel = new Vector(_x,_y,_z);
    pos = new Vector();
}

SDL_Rect Bullet::GetHitBox() {

    hitBox.x = pos->x;
    hitBox.y = pos->y;

    return hitBox;
}

bool Bullet::Spawn(Vector &v)
{
    bool spawned = true;

    image = gameEngine::getInstance()->LoadTexture("bullet.png");
    spawnFX = Mix_LoadWAV( "shotgun.ogg" );
    // int w, h;
    //printf( "RENDER THE PLAYER TEXTURE!\n" );
    SDL_QueryTexture(image, NULL, NULL, &imgWidth, &imgHeight);



    // SDL_QueryTexture(image,NULL,NULL, &imgWidth, &imgHeight);

    clip.x = 0;
    clip.y = 0;
    clip.w = 5;
    clip.h = 19;


    originX = 0;
    originY = 0;

    currentFrame = 0;
    animationDelay=0;
    frameX = 1;
    frameY = 1;
    frameEnd =0;
    frameBegin = 0;
    currentRow = 1;

    //Set the square's dimentions
    hitBox.w = clip.w;
    hitBox.h =clip.h;

    //std::cout << "SPAWN THE BULLET  with image height is " << imgHeight<<  std::endl;

    if(image == NULL)  {
        std::cout << "COULD NOT SPAWN BULLET SPRITE " << std::endl;
        spawned = false;
    }
    //moveSpeed = 12.0;
    pos->x =  v.x;
    pos->y = v.y;

    vel->x = vel->x * moveSpeed;
    vel->y = vel->y * moveSpeed;

    Mix_PlayChannel( -1, spawnFX, 0 );
    //std::cout << "BULLET SPAWNED =  " << spawned<<  std::endl;
    return spawned;

}


void Bullet::Update()
{
    //float frameMoveSpeed = moveSpeed;
   // printf( "UPDATE BEULLET--------------------\n" );



    Vector updatePos = (*vel) * (gameEngine::getInstance()->getTimer() / FRAME_RATE);

    (*this->pos) += updatePos;



    /*
  Vector moveOffset = Vector(vel->x,vel->y,vel->z);
  moveOffset*(gameEngine::getInstance()->gameTimer / 1000);

  //vel *= (gameEngine::getInstance()->gameTimer / 1000);

  (*this->pos) += moveOffset;

  */
}

void Bullet::Draw(SDL_Renderer *renderer)
{
    gameEngine::getInstance()->RenderTexture(image, pos->x, pos->y,clip.w,clip.h,clip);
    // gameEngine::getInstance()->RenderTexture(image, pos->x, pos->y);

}

Bullet::~Bullet()
{
    delete vel;
    vel = nullptr;
    Mix_FreeChunk(spawnFX);


}

