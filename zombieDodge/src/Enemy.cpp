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

       hitBox.x = pos->x;
       hitBox.y = pos->y;

    return hitBox;
}

bool Enemy::Spawn()
{
    bool spawned = true;

    image = gameEngine::getInstance()->LoadTexture("enemy.png");
    spawnFX = Mix_LoadWAV( "zombieRising.wav" );
    int w, h;
    //printf( "RENDER THE PLAYER TEXTURE!\n" );
    SDL_QueryTexture(image, NULL, NULL, &w, &h);

    //Set the square's dimentions
    hitBox.w = w;
    hitBox.h = h;


    std::cout << "SPAWN THE ENEMY  " <<   std::endl;

    if(image == NULL)  {
        std::cout << "COULD NOT SPAWN PLAYER SPRITE " << std::endl;
        spawned = false;
    }
    //moveSpeed = 12.0;
    vel = new Vector();
    int start = rand() % 4 +1;
    std::cout << "-------------------------START ENEMY POSISIOTN = " << start << std::endl;
    switch(start) {

        case 1:

            pos->x = static_cast<float>(rand() % WINDOW_WIDTH + 1);
            pos->y =0.0;
            vel->y = static_cast<float>(rand() % moveSpeed + 1);

            break;

        case 2:

            pos->x =static_cast<float>(rand() % WINDOW_WIDTH + 1);
            pos->y =static_cast<float>(WINDOW_HEIGHT);
            vel->y = -static_cast<float>(rand() % moveSpeed + 1);

            break;

        case 3:
            pos->x =static_cast<float>(WINDOW_WIDTH);
            pos->y =static_cast<float>(rand() % WINDOW_HEIGHT + 1);
            vel->x = -static_cast<float>(rand() % moveSpeed + 1);
            break;

        case 4:
            pos->x =0.0;
            pos->y =static_cast<float>(rand() % WINDOW_HEIGHT + 1);
            vel->x = static_cast<float>(rand() % moveSpeed + 1);
            break;


    }

   // vel->z = 0.0;
    Mix_PlayChannel( -1, spawnFX, 0 );
    return spawned;

}


void Enemy::Update()
{
    //float frameMoveSpeed = moveSpeed;
    printf( "UPDATE ENEMY--------------------\n" );



    Vector updatePos = (*vel) * (gameEngine::getInstance()->getTimer() / FRAME_RATE);
    // std::cout << "timer -> " << gEngine->getTimer() << std::endl;
    std::cout << "DONE ENEMY  MOVE -> VEL = x=" << vel->x << "Y = " << vel->y << std::endl;
    (*this->pos) += updatePos;

    std::cout << "DONE ENEMY  MOVE -> POS = x=" << pos->x << "Y = " << pos->y << std::endl;

      /*
    Vector moveOffset = Vector(vel->x,vel->y,vel->z);
    moveOffset*(gameEngine::getInstance()->gameTimer / 1000);

    //vel *= (gameEngine::getInstance()->gameTimer / 1000);

    (*this->pos) += moveOffset;

    */
}

void Enemy::Draw(SDL_Renderer *renderer)
{

    gameEngine::getInstance()->RenderTexture(image, pos->x, pos->y);

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

