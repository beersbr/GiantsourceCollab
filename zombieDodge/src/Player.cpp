#include "Player.h"
#include "gameEngine.h"

Player::Player()
{

    hitPoints = exp = 0;
    playerId = "player1";
    pos->x = 300;
    pos->y = 300;
    pos->z = 0;
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
    spawned =false;

}


bool Player::Spawn()
    {

    bool spriteCreated = false;
    gameEngine* gEngine = gameEngine::getInstance();

        /*
    printf( "CREATE SPRITE\n" );
    sprite = new Sprite("player1Sprite.png", pos->x, pos->y, 34,94);

    printf( "SET ANIMATION of PLAYER\n" );
    sprite->SetUpAnimation(2,1);
    printf( "SET ORIGIN OF PLAYER\n" );
    sprite->SetOrigin(34/2.0f, 94);

     */


    image = gEngine->LoadTexture("player1Sprite.png");

    int w, h;
        //printf( "RENDER THE PLAYER TEXTURE!\n" );
    //SDL_QueryTexture(image, NULL, NULL, &w, &h);

        //Set the square's dimentions
   // hitBox.w = w;
    //hitBox.h = h;

    std::cout << "SPAWN THE PLAYER  " <<   std::endl;

    //SDL_DestroyTexture(tempSurface);


    if(image == NULL)  {
        //spawned = false;
        std::cout << "COULD NOT SPAWN PLAYER SPRITE " << std::endl;

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
{      std::cout << "UPDATE PLAYER  -> " << std::endl;
    float frameMoveSpeed = this->moveSpeed;
    Vector moveOffset = Vector();
    //sprite->PlayAnimation(1,2,1,200);
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

    //sprite->SetPosition(pos->x, pos->y);



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
    std::cout << "--------SPRITE DRAW=" << std::endl;
    //sprite->Draw(renderer, pos->x, pos->y);
    std::cout << "DONE DRAWING" << std::endl;
    gameEngine::getInstance()->RenderTexture(image, pos->x, pos->y,34,94);

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

