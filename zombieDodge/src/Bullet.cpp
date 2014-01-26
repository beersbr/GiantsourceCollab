#include "Bullet.h"
#include "gameEngine.h"


Bullet::Bullet(Vector* origin, Vector *_target,float _x, float _y, float _z)
{

      if (origin != NULL) {
          printf("CREATE NEW MOUSE BULLET\n");
          std::cout << "_target " << _target->x << " / " <<  _target->x << std::endl;
         // std::cout << "vel " << vel->x << " / " << vel->y << std::endl;

          pos = new Vector(origin->x, origin->y, origin->z);
          target = new Vector(_target->x, _target->y, _target->z);
          vel = new Vector();
      } else {
          vel = new Vector(_x,_y,_z);
          pos = new Vector();

      }

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
    sprite = new Sprite( gameEngine::getInstance()->gameRender,"bullet.png", 0, 0, 5,19,0,0);
    //Set Sprite Rows / Cols
    sprite->SetUpAnimation(1,1);
    //Set Origin to Sprite
    sprite->SetOrigin(5/2.0f, 19);

    spawnFX = Mix_LoadWAV( "shotgun.ogg" );
    Mix_VolumeChunk(spawnFX, 10);


    //target = new Vector(target->x,target->y,target->z);
    if (target != NULL) {
        //target = _target;

        Vector shootDirection = (*target) - (*pos);


        Vector tmp =  shootDirection.toUnit() * moveSpeed;
        //printf("SPAWN MOUSE BULLEt ALMOST");
        (*vel) = tmp;

    } else {
        pos->x = v.x;
        pos->y =  v.x;
        std::cout << "BULLET POS =  " <<  pos->x << " / " << pos->y <<  std::endl;
        printf("CREATE BULLET2");

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

    }


    Mix_PlayChannel( -1, spawnFX, 0 );

    //std::cout << "BULLET SPAWNED =  " << spawned<<  std::endl;
    return spawned;

}


void Bullet::Update()
{
    //float frameMoveSpeed = moveSpeed;
   // printf( "UPDATE BEULLET--------------------\n" );

     /*
    if (target != nullptr) {

        Vector shootDirection = (*target) - (*pos);

        (*vel) = shootDirection.toUnit() * moveSpeed;

    }
    */
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

