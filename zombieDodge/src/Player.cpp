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

    bool spriteCreated = true;

    spawned = true;
    //Create Sprite
    sprite = new Sprite( gameEngine::getInstance()->gameRender,"player1Sprite.png", pos->x, pos->y, 41,101,0,0);
    //Set Sprite Rows / Cols
    sprite->SetUpAnimation(2,1);
    //Set Origin to Sprite
    sprite->SetOrigin(41/2.0f, 101);

    //Set the square's dimentions
    hitBox.w = clip.w;
    hitBox.h = clip.h;


        return spriteCreated;

}
SDL_Rect Player::GetHitBox() {

    hitBox.x = pos->x;
    hitBox.y = pos->y;

    return hitBox;
}
void Player::Update()
{    std::cout << "UPDATE PLAYER  -> " << std::endl;
    float frameMoveSpeed = this->moveSpeed;
    Vector moveOffset = Vector();
    //frameCount++;

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

    }
    std::cout << "KEYDOWN IN PLAYER  -> " << InputHandler::getInstance()->keyIsDown(SDL_SCANCODE_W) << std::endl;

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

    //Update Position
    (*this->pos) += moveOffset;

    //Play Sprite Animation
    sprite->PlayAnimation(0, 1, 1, 200);

    //Update Sprite Position
    sprite->SetPosition(pos->x, pos->y);

     /*
    for (auto b=bullets.begin(); b!=bullets.end(); ++b)  {

        b->second->Update();

    }
    */


}

void Player::Shoot(int _x, int _y)
{

    if(!isShooting){

        isShooting = true;
        // spawn a bullet with the direction
        Bullet *bullet = new Bullet(static_cast<float>(_x),static_cast<float>(_y),0.0);
        bullet->Spawn((*pos));
        //gameEngine::getInstance()->addBullet(bullet);
        gameEngine::getInstance()->bullets.push_back(bullet);
        bullet = nullptr;
        shotsFired++;
        lastShotTime = SDL_GetTicks();

    } else {

        if (lastShotTime+shootInterval < SDL_GetTicks())
        {
            isShooting = false;
            lastShotTime = 0.0;
        }



    }

    if (lastShotTime+shootInterval < SDL_GetTicks())
    {
        if(!isShooting){



        } else {
            isShooting = false;

        }

    }


}

void Player::Draw(SDL_Renderer *renderer){

    sprite->Render(pos->x, pos->y);

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

