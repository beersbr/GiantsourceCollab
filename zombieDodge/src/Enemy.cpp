#include "Enemy.h"
#include "gameEngine.h"

Enemy::Enemy()
{
    printf( "CREATE ENEMY\n" );
    hitPoints = exp = 0;
    enemyId = "enemy1";
    pos->x = 0;
    pos->y = 0;

    //Initialize the offsets
    hitBox.x = 0;
    hitBox.y = 0;



}

Enemy::Enemy(int _x, int _y, int _z, std::string _playerTarget, int _hp)
{

    hitPoints = _hp;
    int exp = 0;
    enemyId = _playerTarget;

}

SDL_Rect Enemy::GetHitBox() {

    hitBox.x = (pos->x- cameraOffset.x);
    hitBox.y = (pos->y- cameraOffset.y);

    return hitBox;
}

bool Enemy::Spawn()
{
    bool spawned = false;

    sprite = new Sprite( gameEngine::getInstance()->gameRender,"zombieSprite.png", pos->x, pos->y, 70,70,0,0);

    sprite->SetUpAnimation(4,1);
    sprite->SetOrigin(70/2.0f, 70);

    spawnFX = Mix_LoadWAV( "zombieRising.wav" );
    if ( spawnFX == NULL)
    {
        std::cout << "Couldn't Load SPAWN FX : zombieRising.wav" << std::endl;
    }  else {
        Mix_VolumeChunk(spawnFX, 50);

    }



    hitBox.w = 70;
    hitBox.h = 70;


    vel = new Vector();
    int start = rand() % 4 +1;
    switch(start) {

        case 1:

            pos->x = static_cast<float>(rand() % (WINDOW_WIDTH+gameEngine::getInstance()->camera.x) + 1);
            pos->y =0.0+gameEngine::getInstance()->camera.y;
            sprite->Rotate(-90);
            vel->y = static_cast<float>(rand() % moveSpeed + 1);

            break;

        case 2:

            pos->x =static_cast<float>(rand() % (WINDOW_WIDTH+gameEngine::getInstance()->camera.x) + 1);
            pos->y =static_cast<float>(WINDOW_HEIGHT+gameEngine::getInstance()->camera.y);
            sprite->Rotate(90);
            vel->y = -static_cast<float>(rand() % moveSpeed + 1);

            break;

        case 3:
            pos->x =static_cast<float>(WINDOW_WIDTH+gameEngine::getInstance()->camera.x);

            pos->y =static_cast<float>(rand() % (WINDOW_HEIGHT+gameEngine::getInstance()->camera.y) + 1);
            vel->x = -static_cast<float>(rand() % moveSpeed + 1);

            break;

        case 4:
            pos->x =0.0+gameEngine::getInstance()->camera.x;
            sprite->Flip('h');
            pos->y =static_cast<float>(rand() % (WINDOW_HEIGHT+gameEngine::getInstance()->camera.y) + 1);
            vel->x = static_cast<float>(rand() % moveSpeed + 1);
            break;


    }

    Mix_PlayChannel( -1, spawnFX, 0 );
    return spawned;

}


void Enemy::Update()
{
    sprite->PlayAnimation(0, 3, 1, 200);

    Vector updatePos = (*vel) * (gameEngine::getInstance()->getTimer() / FRAME_RATE);

    (*this->pos) += updatePos;

    sprite->SetPosition(pos->x, pos->y);

}

void Enemy::Draw(SDL_Renderer *renderer, SDL_Rect *camera)
{

    cameraOffset.x = camera->x;
    cameraOffset.y = camera->y;

    sprite->Render((pos->x-camera->x), (pos->y-camera->y));


}


void Enemy::TakeDamage(int dmg)
{


}


Enemy::~Enemy()
{
    delete vel;
    vel = nullptr;
    Mix_FreeChunk(spawnFX);

    hitPoints = exp = 0;
}

