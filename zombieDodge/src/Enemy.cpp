#include "Enemy.h"
#include "gameEngine.h"

Enemy::Enemy()
{

    hitPoints = exp = 0;
    enemyId = "enemy1";
    pos->x = 300;
    pos->y = 300;

}

Enemy::Enemy(int _x, int _y, int _z, std::string _playerTarget, int _hp)
{

    hitPoints = _hp;
    int exp = 0;
    enemyId = _playerTarget;

}


bool Enemy::Spawn()
{

    bool spawned = true;
    gameEngine* gEngine = gameEngine::getInstance();


    image = gEngine->LoadTexture("zombie.png");
    //Draw the image
    //gEngine->RenderTexture(image, gEngine->gameRender, 300, 400);

    std::cout << "SPAWN THE PLAYER  " <<   std::endl;

    //SDL_DestroyTexture(tempSurface);


    if(image == NULL)  {
        //spawned = false;
        std::cout << "COULD NOT SPAWN PLAYER SPRITE " << std::endl;

    }

    return spawned;

}


void Player::Update()
{
    float frameMoveSpeed = this->moveSpeed;
    Vector moveOffset = Vector();

    if(InputHandler::getInstance()->keyIsDown(SDL_SCANCODE_W)){
        moveOffset.y -= frameMoveSpeed;
    }
    if(InputHandler::getInstance()->keyIsDown(SDL_SCANCODE_S)){
        moveOffset.y += frameMoveSpeed;
    }
    if(InputHandler::getInstance()->keyIsDown(SDL_SCANCODE_A)){
        moveOffset.x -= frameMoveSpeed;
    }
    if(InputHandler::getInstance()->keyIsDown(SDL_SCANCODE_D)){
        moveOffset.x += frameMoveSpeed;
    }

    (*this->pos) += moveOffset;
}

/*
void Player::Move()
{
   // std::cout << "IN PLAYER MOVE FUNCTION TYPE = " << event.type << std::endl;

        gameEngine* gEngine = gameEngine::getInstance();
        Vector updatePos = (*pos) * (gEngine->getTimer() / FRAME_RATE);
       // std::cout << "timer -> " << gEngine->getTimer() << std::endl;
        std::cout << "DONE PLAYER  MOVE -> " << std::endl;
        (*pos) = updatePos + (*pos);

}
*/

void Enemy::Draw(SDL_Renderer *renderer)
{
    //std::cout << "RENDER PLAYER TEXTURE -> " << std::endl;
    gameEngine* gEngine = gameEngine::getInstance();
    std::cout << "POS x IN DRAW-> " << pos->x << std::endl;
    std::cout << "POS y  in DRAW" << pos->y << std::endl;
    // gEngine->RenderTexture(image, 300, 200);
    gEngine->RenderTexture(image, pos->x, pos->y);

}


void Enemy::TakeDamage(int dmg)
{


}


Enemy::~Enemy()
{
    delete vel;
    vel = nullptr;

    hitPoints = exp = 0;
}

