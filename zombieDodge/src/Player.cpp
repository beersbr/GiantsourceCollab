
#include <SDL2/SDL.h>
#include "config.h"
#include <SDL2_image/SDL_image.h>
#include "gameEngine.h"

Player::Player()
{

    hitPoints = exp = 0;
    playerId = "player1";
    pos->x = 300;
    pos->y = 300;

}

Player::Player(int _x, int _y, int _z, std::string _playerTarget, int _hp)
{

    hitPoints = _hp;
    int exp = 0;
    playerId = _playerTarget;

}


bool Player::Spawn()
    {

    bool spawned = true;
    gameEngine* gEngine = gameEngine::getInstance();


    image = gEngine->LoadTexture("player.png");
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


void Player::Move(SDL_Event& event)
{
    gameEngine* gEngine = gameEngine::getInstance();
    float frameMoveSpeed = this->moveSpeed;
    //zombieGame* game = zombieGame::getInstance();

    if(event.type == SDL_KEYDOWN ) {
        //Select surfaces based on key press

        if (event.key.keysym.sym== SDLK_RSHIFT) {
            if(! isSprinting){

                nonSprintElapsedTime += gEngine->getTimer();

                if(nonSprintElapsedTime > sprintInterval || lastSprintTime == -1){
                    frameMoveSpeed = sprintSpeed;
                    isSprinting = true;
                   // lastSprintTime = +(new Date());
                    nonSprintElapsedTime = 0;
                    sprintLength +=  gEngine->getTimer();
                }

            }
            else{

                 sprintElapsedTime += gEngine->getTimer();
                 if(sprintElapsedTime > sprintTime){
                     isSprinting = false;
                     sprintElapsedTime = 0;
                 }
                 else{
                     frameMoveSpeed = sprintSpeed;
                     sprintLength += gEngine->getTimer();
                 }

            }
        }
        else {

             // Not sprinting
             isSprinting = false;
             sprintElapsedTime = 0;
             nonSprintElapsedTime += gEngine->getTimer();
             if(nonSprintElapsedTime > sprintInterval) sprintLength = 0;

        }



        switch( event.key.keysym.sym ) {

            case SDLK_w: pos->y -= frameMoveSpeed; break;
            case SDLK_s: pos->y += frameMoveSpeed; break;
            case SDLK_a: pos->x -= frameMoveSpeed; break;
            case SDLK_d: pos->x += frameMoveSpeed; break;

            case SDLK_UP: Shoot(0,-1);; break;
            case SDLK_DOWN:Shoot(0,1);
            case SDLK_LEFT: Shoot(-1,0);
            case SDLK_RIGHT: Shoot(1,0); break;
        }


    }

        Vector updatePos = (*pos) * (gEngine->getTimer() / FRAME_RATE);
        (*pos) = updatePos + (*pos);
}

void Player::Draw()
{
    //std::cout << "RENDER PLAYER TEXTURE -> " << std::endl;
   // gameEngine* gEngine = gameEngine::getInstance();

  //  gEngine->RenderTexture(image, 300, 400);

}


void Player::Shoot(int _x, int _y)
{


}

void Player::Update(SDL_Event& event)
{
        Move(event);

}

void Player::Update()
{

}

void Player::TakeDamage(int dmg)
{


}


Player::~Player()
{
	//delete vel;
	//vel = nullptr;

    hitPoints = exp = 0;
}

