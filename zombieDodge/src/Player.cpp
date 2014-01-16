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


void Player::Update(SDL_Event& event)
{

    std::cout << "UPDATING PLAYER -> " << std::endl;
    Move();

}
void Player::Update()
{
    float frameMoveSpeed = 1.5;
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

void Player::HandleInput(SDL_Event& event) {


        gameEngine* gEngine = gameEngine::getInstance();
        //std::cout << "KY PRESSED IN PLAYER " << event.key.keysym.sym << std::endl;

        float frameMoveSpeed = this->moveSpeed;
        //std::cout << "MOVING PLAYER -> " << std::endl;
        //zombieGame* game = zombieGame::getInstance();


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

            case SDLK_w: pos->y -= frameMoveSpeed;

                std::cout << "-----------------------MOVE UP---------------------------" << std::endl;

                break;

            case SDLK_s: pos->y += frameMoveSpeed;
                std::cout << "-----------------------MOVE DOWN---------------------------" << std::endl;

                break;
            case SDLK_a: pos->x -= frameMoveSpeed;
                std::cout << "-----------------------MOVE LEFT---------------------------" << std::endl;
                break;


            case SDLK_d: pos->x += frameMoveSpeed;
                std::cout << "-----------------------MOVE RIGHT---------------------------" << std::endl;

                break;

            case SDLK_UP: Shoot(0,-1);; break;
            case SDLK_DOWN:Shoot(0,1);
            case SDLK_LEFT: Shoot(-1,0);
            case SDLK_RIGHT: Shoot(1,0); break;
            default: break;
        }

}

void Player::Move()
{
   // std::cout << "IN PLAYER MOVE FUNCTION TYPE = " << event.type << std::endl;

        gameEngine* gEngine = gameEngine::getInstance();
        Vector updatePos = (*pos) * (gEngine->getTimer() / FRAME_RATE);
       // std::cout << "timer -> " << gEngine->getTimer() << std::endl;
        std::cout << "DONE PLAYER  MOVE -> " << std::endl;
        (*pos) = updatePos + (*pos);

}

void Player::Shoot(int _x, int _y)
{


}

void Player::Draw(SDL_Renderer *renderer)
{
    //std::cout << "RENDER PLAYER TEXTURE -> " << std::endl;
    gameEngine* gEngine = gameEngine::getInstance();
    std::cout << "POS x IN DRAW-> " << pos->x << std::endl;
    std::cout << "POS y  in DRAW" << pos->y << std::endl;
    // gEngine->RenderTexture(image, 300, 200);
    gEngine->RenderTexture(image, pos->x, pos->y);

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

