#include "Enemy.h"
#include "gameEngine.h"

Enemy::Enemy()
{
    printf( "CREATE ENEMY\n" );
    hitPoints = exp = 0;
    enemyId = "enemy1";
    pos = new Vector();
    pos->x = 0;
    pos->y = 0;

    //Initialize the offsets
    hitBox.x = 0;
    hitBox.y = 0;
    clip.x = 0;
    clip.y = 0;
    clip.w = 70;
    clip.h = 70;



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

    image = gameEngine::getInstance()->LoadTexture("zombieSprite.png");
    spawnFX = Mix_LoadWAV( "zombieRising.wav" );
   // int w, h;
    //printf( "RENDER THE PLAYER TEXTURE!\n" );
    SDL_QueryTexture(image, NULL, NULL, &imgWidth, &imgHeight);



   // SDL_QueryTexture(image,NULL,NULL, &imgWidth, &imgHeight);

    clip.x = 0;
    clip.y = 0;
    clip.w = 70;
    clip.h = 70;


    originX = 0;
    originY = 0;

    currentFrame = 0;
    animationDelay=0;
    frameX = 4;
    frameY = 1;
    frameEnd =3;
    frameBegin = 0;
    currentRow = 1;

    //Set the square's dimentions
    hitBox.w = clip.w;
    hitBox.h =clip.h;

    //std::cout << "SPAWN THE ENEMY  with image height is " << imgHeight<<  std::endl;

    if(image == NULL)  {
        std::cout << "COULD NOT SPAWN PLAYER SPRITE " << std::endl;
        spawned = false;
    }
    //moveSpeed = 12.0;
    vel = new Vector();
    int start = rand() % 4 +1;
   // std::cout << "-------------------------START ENEMY POSISIOTN = " << start << std::endl;
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
   // printf( "UPDATE ENEMY--------------------\n" );



    Vector updatePos = (*vel) * (gameEngine::getInstance()->getTimer() / FRAME_RATE);
    // std::cout << "timer -> " << gEngine->getTimer() << std::endl;
   // std::cout << "DONE ENEMY  MOVE -> VEL = x=" << vel->x << "Y = " << vel->y << std::endl;
    (*this->pos) += updatePos;


    //std::cout << "------------ ENEMY animationDelay" <<animationDelay << std::endl;

    if ( animationDelay==-1) {

        animationDelay = 0;
    }
    if (animationDelay+200 < SDL_GetTicks())
    {
        if (frameEnd <= currentFrame)
            currentFrame = frameBegin;
        else
            currentFrame++;

        clip.x = currentFrame * (imgWidth/frameX);
        clip.y = (currentRow-1) * (imgHeight/frameY);
        clip.w = imgWidth/frameX;
        clip.h = imgHeight/frameY;

        animationDelay = SDL_GetTicks();
    }

    //std::cout << "DONE ENEMY  MOVE -> POS = x=" << pos->x << "Y = " << pos->y << std::endl;

      /*
    Vector moveOffset = Vector(vel->x,vel->y,vel->z);
    moveOffset*(gameEngine::getInstance()->gameTimer / 1000);

    //vel *= (gameEngine::getInstance()->gameTimer / 1000);

    (*this->pos) += moveOffset;

    */
}

void Enemy::Draw(SDL_Renderer *renderer)
{
    gameEngine::getInstance()->RenderTexture(image, pos->x, pos->y,clip.w,clip.h,clip);
   // gameEngine::getInstance()->RenderTexture(image, pos->x, pos->y);

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

