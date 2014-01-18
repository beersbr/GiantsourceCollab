#include "Player.h"
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

    image = new Sprite("player.png", 300,250, 100,120);
        bob->SetUpAnimation(4,4);
        bob->SetOrgin(bob->GetWidth()/2.0f, bob->GetHeight());



    image = gEngine->LoadTexture("player.png");

    int w, h;
        //printf( "RENDER THE PLAYER TEXTURE!\n" );
    SDL_QueryTexture(image, NULL, NULL, &w, &h);

        //Set the square's dimentions
    hitBox.w = w;
    hitBox.h = h;

    std::cout << "SPAWN THE PLAYER  " <<   std::endl;

    //SDL_DestroyTexture(tempSurface);


    if(image == NULL)  {
        //spawned = false;
        std::cout << "COULD NOT SPAWN PLAYER SPRITE " << std::endl;

    }

        return spawned;

}
SDL_Rect Player::GetHitBox() {

    hitBox.x = pos->x;
    hitBox.y = pos->y;

    return hitBox;
}
void Player::Update()
{      std::cout << "UPDATE PLAYER  -> " << std::endl;
    float frameMoveSpeed = this->moveSpeed;
    Vector moveOffset = Vector();




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

   // std::cout << "DONE ENEMY  MOVE -> VEL = x=" << vel->x << "Y = " << vel->y << std::endl;
    (*this->pos) += moveOffset;

    std::cout << "---------DONE PLAYER  MOVE -> POS = x=" << pos->x << "Y = " << pos->y << std::endl;


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


}

void Player::Draw(SDL_Renderer *renderer)
{
    gameEngine::getInstance()->RenderTexture(image, pos->x, pos->y);

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

