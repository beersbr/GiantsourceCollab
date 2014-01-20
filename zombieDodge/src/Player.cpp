#include "Player.h"
#include "gameEngine.h"

Player::Player()
{

    hitPoints = exp = 0;
    playerId = "player1";
    pos = new Vector(300,300,0);
   // SDL_Rect clip;
    clip.x = 0;
    clip.y = 0;
    clip.w = 41;
    clip.h = 101;
    spawned =false;


}

Player::Player(float _x, float _y, float _z, std::string _playerTarget, int _hp)
{

    hitPoints = _hp;
    int exp = 0;
    playerId = _playerTarget;
    pos->x = _x;
    pos->y = _y;
    pos->z = _z;
    // SDL_Rect clip;
    clip.x = 0;
    clip.y = 0;
    clip.w = 41;
    clip.h = 101;
    spawned =false;

}


bool Player::Spawn()
    {

    bool spriteCreated = false;
    gameEngine* gEngine = gameEngine::getInstance();
    //sprite = new Sprite("player1Sprite.png", pos->x, pos->y, 41,101);

    //sprite->SetUpAnimation(2,1);
    //sprite->SetOrigin(41/2.0f, 101);


        /*
    printf( "CREATE SPRITE\n" );


    printf( "SET ANIMATION of PLAYER\n" );

    printf( "SET ORIGIN OF PLAYER\n" );


     */


    image = gEngine->LoadTexture("player1Sprite.png");


     SDL_QueryTexture(image,NULL,NULL, &imgWidth, &imgHeight);

     clip.x = 0;
     clip.y = 0;
     clip.w = 41;
     clip.h = 101;

     originX = 0;
     originY = 0;

     currentFrame = 0;
     frameX = 2;
     frameY = 1;
     frameEnd =1;
     frameBegin = 0;
     currentRow = 1;
        animationDelay=0;

    //int w, h;
        //printf( "RENDER THE PLAYER TEXTURE!\n" );
    //SDL_QueryTexture(image, NULL, NULL, &w, &h);

        //Set the square's dimentions
    hitBox.w = clip.w;
    hitBox.h = clip.h;

    //std::cout << "SPAWN THE PLAYER  " <<   std::endl;

    //SDL_DestroyTexture(tempSurface);


    if(image == NULL)  {
        //spawned = false;
        std::cout << "COULD NOT SPAWN PLAYER SPRITE " << std::endl;
        spriteCreated = false;
    }  else {

        spawned = true;
        spriteCreated = true;
    }

        return spriteCreated;

}
SDL_Rect Player::GetHitBox() {

    hitBox.x = pos->x;
    hitBox.y = pos->y;

    return hitBox;
}
void Player::Update()
{     // std::cout << "UPDATE PLAYER  -> " << std::endl;
    float frameMoveSpeed = this->moveSpeed;
    Vector moveOffset = Vector();
    frameCount++;

    //sprite->PlayAnimation(0,1,1,200, clip,82,101);
    if(InputHandler::getInstance()->keyIsDown( SDL_SCANCODE_LSHIFT)) {
        if(! isSprinting){

            nonSprintElapsedTime += gameEngine::getInstance()->getTimer();

            if(nonSprintElapsedTime > sprintInterval || lastSprintTime == -1){
                frameMoveSpeed = sprintSpeed;
                isSprinting = true;
                // lastSprintTime = +(new Date());
                nonSprintElapsedTime = 0;
                sprintLength +=  gameEngine::getInstance()->getTimer();
            }

        }
        else{

            sprintElapsedTime += gameEngine::getInstance()->getTimer();
            if(sprintElapsedTime > sprintTime){
                isSprinting = false;
                sprintElapsedTime = 0;
            }
            else{
                frameMoveSpeed = sprintSpeed;
                sprintLength += gameEngine::getInstance()->getTimer();
            }

        }
    }
    else {

        // Not sprinting
        isSprinting = false;
        sprintElapsedTime = 0;
        nonSprintElapsedTime += gameEngine::getInstance()->getTimer();
        if(nonSprintElapsedTime > sprintInterval) sprintLength = 0;

        /*
         case SDLK_UP: Shoot(0,-1);; break;
         case SDLK_DOWN:Shoot(0,1);
         case SDLK_LEFT: Shoot(-1,0);
         case SDLK_RIGHT: Shoot(1,0); break;
         default: break;
         */
    }


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


    if(InputHandler::getInstance()->keyIsDown(SDL_SCANCODE_LEFT)){
        Shoot(-1, 0);

    }
    if(InputHandler::getInstance()->keyIsDown(SDL_SCANCODE_RIGHT)){
        Shoot(1, 0);
    }
    if(InputHandler::getInstance()->keyIsDown(SDL_SCANCODE_UP)){
        Shoot(0, -1);
    }
    if(InputHandler::getInstance()->keyIsDown(SDL_SCANCODE_DOWN)){
        Shoot(0, 1);
    }

   // std::cout << "DONE ENEMY  MOVE -> VEL = x=" << vel->x << "Y = " << vel->y << std::endl;
    (*this->pos) += moveOffset;

    //std::cout << "animationDelay" << animationDelay << std::endl;
    if (animationDelay+200 < SDL_GetTicks())
    {

        //std::cout << "CHANGE THE FRAME=" << currentFrame << std::endl;
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
     /*
    for (auto b=bullets.begin(); b!=bullets.end(); ++b)  {

        b->second->Update();

    }
    */
    //sprite->SetPosition(pos->x, pos->y);



    //std::cout << "---------DONE PLAYER  MOVE -> POS = x=" << pos->x << "Y = " << pos->y << std::endl;


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
void Player::Shoot(int _x, int _y)
{
    Bullet* bullet = new Bullet(static_cast<float>(_x),static_cast<float>(_y),0.0);
    bullet->Spawn((*pos));
    gameEngine::getInstance()->bullets[bulletCnt] = bullet;
    //bullets[bulletCnt] = bullet;
    bulletCnt++;

}

void Player::Draw(SDL_Renderer *renderer){

    //clipx = 0;
    /*

    */
    //sprite->Draw(pos->x, pos->y);

    //SDL_Texture* pImage = sprite->image;


    //clip.x=41;
    gameEngine::getInstance()->RenderTexture(image, pos->x, pos->y,clip.w,clip.h,clip);



}


void Player::TakeDamage(int dmg)
{


}


Player::~Player()
{
	delete vel;
	vel = nullptr;

    hitPoints = exp = 0;
}

