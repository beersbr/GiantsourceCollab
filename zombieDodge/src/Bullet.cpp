#include "Bullet.h"
#include "gameEngine.h"


Bullet::Bullet(Vector* origin, Vector *_target,float _x, float _y, float _z,std::string owner, std::string type)
{

      if (origin != NULL) {
          pos = new Vector(origin->x, origin->y, origin->z);
          target = new Vector(_target->x, _target->y, _target->z);
          vel = new Vector();
      } else {
          vel = new Vector(_x,_y,_z);
          pos = new Vector();
      }
      ownerId = owner;
      ownerType = type;

}

SDL_Rect Bullet::GetHitBox() {

    hitBox.x = pos->x-cameraOffset.x;
    hitBox.y = pos->y-cameraOffset.y;

    return hitBox;
}

bool Bullet::Spawn(Vector &v)
{
    bool spawned = true;
    cJSON *playersNode = gameEngine::getInstance()->gameConfig->GetNode(NULL,"players");
    cJSON *playerConfig =  gameEngine::getInstance()->gameConfig->GetNode(playersNode,ownerId);
    cJSON *fxNode = gameEngine::getInstance()->gameConfig->GetNode(playerConfig,"fx");
    bulletConfig = gameEngine::getInstance()->gameConfig->GetNode(fxNode,"shoot");
    std:: string spritePath =  gameEngine::getInstance()->gameConfig->GetString("","sprite",bulletConfig);
    // SDL_Rect clip;
    clip.x = 0;
    clip.y = 0;
    moveSpeed =  gameEngine::getInstance()->gameConfig->GetInt("","speed",bulletConfig);
    int w = gameEngine::getInstance()->gameConfig->GetInt("","w",bulletConfig);
    int h = gameEngine::getInstance()->gameConfig->GetInt("","h",bulletConfig);
    //Create Sprite

    sprite = new Sprite( gameEngine::getInstance()->gameRender,spritePath, 0, 0, w,h,0,0,true);
    //Set Sprite Rows / Cols
    sprite->SetUpAnimation(gameEngine::getInstance()->gameConfig->GetInt("","rows",bulletConfig),gameEngine::getInstance()->gameConfig->GetInt("","cols",bulletConfig));
    //Set Origin to Sprite
    sprite->SetOrigin(w/2.0f, h);
    std::string fxPath = gameEngine::getInstance()->gameConfig->GetString("","src",bulletConfig);

    spawnFX = Mix_LoadWAV( fxPath.c_str() );

    Mix_VolumeChunk(spawnFX, 10);
    playersNode = nullptr;
    playerConfig = nullptr;
    fxNode = nullptr;

    if (target != NULL) {
        //If shooting at a point on the screen from mouse click
        double angle = atan2(target->y-pos->y, target->x-pos->x);
        angle = angle * (180/3.14)+90;
        sprite->Rotate(angle);
        Vector shootDirection = (*target) - (*pos);
        Vector tmp =  shootDirection.toUnit() * moveSpeed;
        (*vel) = tmp;

    } else {
        pos->x = v.x;
        pos->y =  v.y;

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

    return spawned;

}


void Bullet::Update()
{
    Vector updatePos = (*vel) * (gameEngine::getInstance()->getTimer() / FRAME_RATE);

    (*this->pos) += updatePos;

    //Play Sprite Animation
    sprite->PlayAnimation(0, 0, 1, 200);

    //Update Sprite Position
    sprite->SetPosition(pos->x, pos->y);
}

void Bullet::Draw(SDL_Renderer *renderer, SDL_Rect *camera)
{
    cameraOffset.x = camera->x;
    cameraOffset.y = camera->y;

    sprite->Render(pos->x-camera->x, pos->y-camera->y);
}

Bullet::~Bullet()
{
    delete vel;
    delete pos;
    pos = nullptr;
    vel = nullptr;
    delete bulletConfig;
    bulletConfig = nullptr;
    Mix_FreeChunk(spawnFX);


}

