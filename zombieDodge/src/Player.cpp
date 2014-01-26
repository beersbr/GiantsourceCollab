#include "Player.h"
#include "gameEngine.h"

Player::Player()
{
    std::string _playerTarget = "player1";

    std::string configUrl = "config/" + _playerTarget + ".config";

    config = Configurator::open(configUrl);

    pos = new Vector(300,300,0);
   // SDL_Rect clip;
    clip.x = 0;
    clip.y = 0;
    spritePath =_playerTarget+ "Sprite.png";
    hitPoints =  atoi((*config)[_playerTarget+"HitPoints"].c_str());
    spriteFrames =  atoi((*config)[_playerTarget+"SpriteFrames"].c_str());
    spriteRows =  atoi((*config)[_playerTarget+"SpriteRows"].c_str());
    exp = 0;
    //clip.w = atoi((*config)[_playerTarget+"ImageCropWidth"].c_str());
    //clip.h = atoi((*config)[_playerTarget+"ImageCropHeight"].c_str());
    clip.w = 41;
    clip.h = 101;

    spawned =false;
    std::cout << "SPRITE PATH =   " <<  spritePath << std::endl;
    playerId = _playerTarget;

    config = nullptr;
}

Player::Player(float _x, float _y, float _z, std::string _playerTarget, int _hp)
{

    std::string configUrl = "config/" + _playerTarget + ".config";

    config = Configurator::open(configUrl);

    pos = new Vector(_x,_y,_z);
    // SDL_Rect clip;
    clip.x = 0;
    clip.y = 0;

    spritePath =((*config)[_playerTarget+"Image"]).c_str();
    std::replace(spritePath.begin(), spritePath.end(), '"', ' ');
    hitPoints =  atoi((*config)[_playerTarget+"HitPoints"].c_str());
    spriteFrames =  atoi((*config)[_playerTarget+"SpriteFrames"].c_str());
    spriteRows =  atoi((*config)[_playerTarget+"SpriteRows"].c_str());
    exp = 0;
    clip.w = atoi((*config)[_playerTarget+"ImageCropWidth"].c_str());
    clip.h = atoi((*config)[_playerTarget+"ImageCropHeight"].c_str());
    spawned =false;
    playerId = _playerTarget;
    //std::cout << "SPRITE PATH =   " <<  spritePath << std::endl;
    config = nullptr;

}


bool Player::Spawn()
    {

    bool spriteCreated = true;

    spawned = true;

    //Create Sprite
    sprite = new Sprite( gameEngine::getInstance()->gameRender,spritePath, pos->x, pos->y, clip.w,clip.h,0,0);
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

    hitBox.x = pos->x - cameraOffset.x;
    hitBox.y = pos->y - cameraOffset.y;

    return hitBox;
}
void Player::Update()
{    //std::cout << "UPDATE PLAYER  -> " << std::endl;
    float frameMoveSpeed = this->moveSpeed;
    Vector moveOffset = Vector();

    if(InputHandler::getInstance()->keyIsDown( SDL_SCANCODE_LSHIFT)) {


        if(!isSprinting){

            nonSprintElapsedTime += gameEngine::getInstance()->getTimer();

            if(nonSprintElapsedTime > sprintInterval || lastSprintTime == -1){
                frameMoveSpeed = sprintSpeed;
                isSprinting = true;
                lastSprintTime = SDL_GetTicks();
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

        //frameMoveSpeed = sprintSpeed;
    }
    else {

        // Not sprinting
        isSprinting = false;
        sprintElapsedTime = 0;
        nonSprintElapsedTime += gameEngine::getInstance()->getTimer();
        if(nonSprintElapsedTime > sprintInterval) sprintLength = 0;

    }
    //std::cout << "KEYDOWN IN PLAYER  -> " << InputHandler::getInstance()->keyIsDown(SDL_SCANCODE_W) << std::endl;

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



    if(InputHandler::getInstance()->mouseButtonIsDown()){

            MouseShoot();

    }



    //std::cout << "--------pos PRE x / y  -> " << pos->x << " / " << pos->y << std::endl;
    //Update Position
    (*this->pos) += moveOffset;


    if (pos->x > (gameEngine::getInstance()->levelWidth-clip.w)) {

        pos->x = (gameEngine::getInstance()->levelWidth-clip.w);

    } else if (pos->x < 0) {

        pos->x = 0;
    }

    if (pos->y > (gameEngine::getInstance()->levelHeight-clip.h)) {

        pos->y = (gameEngine::getInstance()->levelHeight-clip.h);
    } else if (pos->y < clip.h) {

        pos->y = clip.h;
    }

    //std::cout << "pos x / y  -> " << pos->x << " / " << pos->y << std::endl;


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

void Player::MouseShoot() {



     int _x; int _y;

    if(!isShooting){

        isShooting = true;
        // spawn a bullet with the direction

        Vector* mVector = new Vector(gameEngine::getInstance()->mouseX+gameEngine::getInstance()->camera.x,gameEngine::getInstance()->mouseY+gameEngine::getInstance()->camera.y,0);

        Bullet *bullet = new Bullet(pos,mVector,NULL, NULL, NULL);

        bullet->Spawn((*pos));

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

void Player::Shoot(int _x, int _y)
{

    if(!isShooting){

        isShooting = true;
        // spawn a bullet with the direction
        Bullet *bullet = new Bullet(NULL, NULL, _x,_y,0.0);
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

void Player::Draw(SDL_Renderer *renderer, SDL_Rect *camera){

    cameraOffset.x = camera->x;
    cameraOffset.y = camera->y;

   // std::cout << "CAMERA x/y =   " <<  camera->x << " / " << camera->y << std::endl;
    sprite->Render((pos->x-camera->x), (pos->y-camera->y));

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

