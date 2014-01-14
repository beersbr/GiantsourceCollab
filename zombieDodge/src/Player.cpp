
#include <SDL2/SDL.h>
#include "config.h"
#include <SDL2_image/SDL_image.h>
#include "gameEngine.h"

Player::Player()
{

    gameEngine* gEngine = gameEngine::getInstance();
    hitPoints = exp = 0;
    image =gEngine->LoadImage( "player.png" );
}

Player::Player(int _x, int _y, int _z, std::string _playerTarget, int _hp)
{
    //Entity(_x,_y,_z);
    gameEngine* gEngine = gameEngine::getInstance();
    hitPoints = _hp;
    int exp = 0;
    std::string playerId = _playerTarget;
}


void Player::Spawn()
    {

	SDL_Surface* tempSurface = IMG_Load("player.png");
	
    if(tempSurface == NULL)
		return;

	image = SDL_ConvertSurface(tempSurface, tempSurface->format, NULL);


	if(image == NULL)
	{
		SDL_FreeSurface(tempSurface);
		return;
	}

	SDL_FreeSurface(tempSurface);
	tempSurface = NULL;
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

    gameEngine* gEngine = gameEngine::getInstance();

    gEngine->ApplySurface(static_cast<float>(pos->x), static_cast<float>(pos->y), image, gEngine->getGameSurface() );

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

