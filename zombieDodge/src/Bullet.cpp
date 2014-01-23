#include "Bullet.h"
#include "gameEngine.h"


Bullet::Bullet(float _x, float _y, float _z)
{

    vel = new Vector(_x,_y,_z);
    pos = new Vector();
}

SDL_Rect Bullet::GetHitBox() {

    hitBox.x = pos->x-cameraOffset.x;
    hitBox.y = pos->y-cameraOffset.y;

    return hitBox;
}

bool Bullet::Spawn(Vector &v)
{
    bool spawned = true;

    //Create Sprite
    sprite = new Sprite( gameEngine::getInstance()->gameRender,"bullet.png", v.x, v.y, 5,19,0,0);
    //Set Sprite Rows / Cols
    sprite->SetUpAnimation(1,1);
    //Set Origin to Sprite
    sprite->SetOrigin(5/2.0f, 19);

    spawnFX = Mix_LoadWAV( "shotgun.ogg" );
    Mix_VolumeChunk(spawnFX, 10);

    pos->x =  v.x;
    pos->y = v.y;

    switch(static_cast<int>(vel->x)) {

        case 1:
            sprite->Rotate(90);
            break;

        case -1:
            sprite->Rotate(-90);
            break;


    }
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
    //Play Sprite Animation
    sprite->PlayAnimation(0, 0, 1, 200);

    //Update Sprite Position
    sprite->SetPosition(pos->x, pos->y);


    /*
  Vector moveOffset = Vector(vel->x,vel->y,vel->z);
  moveOffset*(gameEngine::getInstance()->gameTimer / 1000);

  //vel *= (gameEngine::getInstance()->gameTimer / 1000);

  (*this->pos) += moveOffset;

  */
}

void Bullet::Draw(SDL_Renderer *renderer, SDL_Rect *camera)
{
    cameraOffset.x = camera->x;
    cameraOffset.y = camera->y;

    sprite->Render(pos->x-camera->x, pos->y-camera->y);

    //gameEngine::getInstance()->RenderTexture(image, pos->x, pos->y,clip.w,clip.h,clip);
    // gameEngine::getInstance()->RenderTexture(image, pos->x, pos->y);

}

Bullet::~Bullet()
{
    delete vel;
    vel = nullptr;
    Mix_FreeChunk(spawnFX);


}

