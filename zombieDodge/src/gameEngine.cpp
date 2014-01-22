#import "gameEngine.h"

gameEngine* gameEngine::_instance = nullptr;

gameEngine* gameEngine::getInstance() {

    if (!gameEngine::_instance)
        gameEngine::_instance = new gameEngine();

    return gameEngine::_instance;

}

gameEngine::gameEngine() {


    // SDL_Event gameEvent;

}

gameEngine::gameEngine(gameEngine&)
{


}

SDL_Surface* gameEngine::LoadImage( const std::string path )
{

    SDL_Surface* optimizedSurface = NULL;

    //Load image at specified path
    SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
    if( loadedSurface == NULL )
    {
        printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
    }
    else
    {
        //Convert surface to screen format
        optimizedSurface = SDL_ConvertSurface( loadedSurface, gameSurface->format, NULL );
        if( optimizedSurface == NULL )
        {
            printf( "Unable to optimize image %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
        }

        //Get rid of old loaded surface
        SDL_FreeSurface( loadedSurface );
    }

    return optimizedSurface;
}

SDL_Texture* gameEngine::LoadTexture(const std::string &file){

    //printf( "Loading Texture %s:", file.c_str());

    SDL_Texture *texture = IMG_LoadTexture(gameRender, file.c_str());
    if (texture == nullptr)
        printf( "Failed to load  texture!\n %s:", file.c_str() );
    return texture;
}


void gameEngine::RenderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y, int w, int h){
    //Setup the destination rectangle to be at the position we want
    SDL_Rect dst;
    dst.x = x;
    dst.y = y;
    dst.w = w;
    dst.h = h;
    SDL_RenderCopy(ren, tex, NULL, &dst);
}

void gameEngine::RenderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y){
    int w, h;
    //printf( "RENDER THE TEXTURE!\n" );
    SDL_QueryTexture(tex, NULL, NULL, &w, &h);
    RenderTexture(tex, ren, x, y, w, h);
}


bool gameEngine::LoadScreen()
{

    //std::cout << "LOAD BACKGROUND FOR  = " <<  gameState << std::endl;

    //Loading success flag
    bool success = true;
     /*
    CameraX = 300;
    CameraY = 250;

    grass = new Sprite(gameRender,"swamp.jpg", 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, &CameraX, &CameraY);
    MouseX = 0;
    MouseY = 0;
       */


    switch(gameState)

    {
        case SETUP:
        case MENU:
            gameBackground = LoadTexture("welcome.jpg");
            break;

        case PLAYING:
            gameBackground = LoadTexture("swamp.jpg");
            break;

        case GAME_OVER:
            gameBackground = LoadTexture("gameover.jpg");
            break;

        default:
            break;

    }


    if(gameBackground == NULL )
    {
        printf( "Failed to load  image!\n" );
        success = false;

        gameState = CLEANUP;

    }   else {

        success = true;
    }

    return success;
};


bool gameEngine::loadStateResources(int screenId)
{
    //Loading success flag
    bool success = true;

    switch(screenId)

    {
        case 0:

            break;

    }


    return success;
};


bool gameEngine::GameInit () {

    bool gameInit = true;

    printf( "GAME INIT\n" );

    //Load the sound effects

    //Once a config is in place, grab all the user data from the config and create the new player that way,
    //Config playerConfig = getConfig(_playerTarget);

    if (currentPlayer == nullptr) {
        printf( "CREATE PLAYER\n" );
        currentPlayer = new Player();

        currentPlayer->Spawn();
        Enemy *enemy = new Enemy();


        enemy->Spawn();
        enemies.push_back(enemy);
        enemy = nullptr;

    }

    //Also set initial game state object

    return gameInit;

}
bool gameEngine::Setup(){

    config = Configurator::open("config/game.config");

    gameState = SETUP;
    //Initialization flag
    bool success = true;

    gameTimer = SDL_GetTicks();

    //Initialize SDL
    if( SDL_Init( SDL_INIT_EVERYTHING ) < 0 )
    {
        printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
        success = false;
    }
    else
    {
        //Create window
        gameWindow = SDL_CreateWindow(
                ((*config)["window_title"]).c_str(),             // window title
                SDL_WINDOWPOS_CENTERED,     // x position, centered
                SDL_WINDOWPOS_CENTERED,     // y position, centered
                WINDOW_WIDTH,                        // width, in pixels
                WINDOW_HEIGHT,                        // height, in pixels
                NULL
        );
        if( gameWindow == NULL )
        {
            printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
            success = false;
        }
        else
        {
            //Initialize JPG loading
            int imgFlags = IMG_INIT_JPG;
            if( !( IMG_Init( imgFlags ) & imgFlags ) )
            {
                printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
                success = false;
            }
            else
            {

                gameRender = SDL_CreateRenderer(gameWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
                //Get window surface
                //gameSurface = SDL_GetWindowSurface( gameWindow);
            }

            //Initialize SDL_mixer
            if( Mix_OpenAudio( 22050, MIX_DEFAULT_FORMAT, 2, 4096 ) == -1 )
            {
                return false;
            }
        }
    }

    if (success) {

        gameState = MENU;
        LoadScreen();

    }

    return success;

}





void gameEngine::Run() {


    while ( this->gameState != EXIT) {

        if (getTimer() >= FRAME_RATE )
        {
            SDL_Event event;
            while( SDL_PollEvent( &event ) != 0 ){
                switch(event.type)
                {
                    case SDL_KEYDOWN:
                        InputHandler::getInstance()->keyDown(event.key.keysym.scancode);
                        break;
                    case SDL_KEYUP:
                        InputHandler::getInstance()->keyUp(event.key.keysym.scancode);
                        break;
                    case SDL_QUIT:
                        this->gameState = CLEANUP;
                        break;
                }
            }

            switch(this->gameState) {

                case PLAYING:



                    if ((!gameReady)){
                        std::cout << "INIT THE GAME  " <<   std::endl;
                        gameReady = GameInit();

                        if ((!gameReady)) {

                            this->gameState = CLEANUP;
                        }

                     }

                case GAME_OVER:




                 default:


                    break;



            }

            this->Update();

            this->Draw();

            gameTimer = SDL_GetTicks();

        }

        if (gameState == CLEANUP) {

            Cleanup();

        }

    }
}


void gameEngine::Update() {

    switch(gameState) {

        case SETUP:

            //this->loadStateResources( this->currentGameState);
            break;

        case MENU:

            this->MenuInput();

            break;

        case PLAYING:

            this->GameInput();
            if (gameReady){
                //Update the Player
                if (currentPlayer->spawned == true) {
                    currentPlayer->Update();
                }

                for(std::vector<Bullet*>::iterator bt = bullets.begin(); bt != bullets.end();) {

                    (*bt)->Update();
                    ++bt;

                }

                   if (enemyCnt> 15) {

                        totalEnemyCnt++;
                        std::string enemyType;

                        Enemy *e = new Enemy();
                        e->Spawn();
                        if (followEnemyCnt == 7) {

                           e->isFollow = true;
                           followEnemyCnt = 0;
                        }

                         followEnemyCnt++;

                         enemies.push_back(e);
                         //delete enemy;
                          e= nullptr;

                         enemyCnt = 0;
                   }


                enemyCnt++;
               // }


                for(std::vector<Enemy*>::iterator et = enemies.begin(); et != enemies.end();) {

                    if ( (*et)->isFollow) {

                        Enemy* em = *et;

                        Vector moveEnemy = ((*currentPlayer->pos) - (*em->pos));

                        (*em->vel) =   ((moveEnemy.toUnit()) * ((*et)->moveSpeed));

                    }

                    (*et)->Update();



                    for(std::vector<Bullet* >::iterator bt = bullets.begin(); bt != bullets.end();) {

                        if((CheckCollision((*et)->GetHitBox(), (*bt)->GetHitBox()) ))
                        {

                            (*et)->deleteItem = true;
                              //et = enemies.erase(et);
                              bt = bullets.erase(bt);
                              bt = bullets.end();

                        }  else {
                            //++b;
                            ++bt;
                        }

                    }

                    if ((*et)->deleteItem) {
                        et = enemies.erase(et);

                    }   else {
                        if((CheckCollision((*et)->GetHitBox(), currentPlayer->GetHitBox() ) ))
                        {
                            printf("GAMEOVER\n");
                            et = enemies.end();
                            gameState = GAME_OVER;
                        } else {

                            ++et;

                        }



                    }


                }

            }
            //Update the Monsters

            //Update the Bullets

            //General Game input handler

            break;

        case GAME_OVER:
            LoadScreen();
            this->MenuInput();
            break;

        default:
            break;



    }

    Draw();



}

void gameEngine::addBullet(Bullet* b) {
    //printf("ADD A BULLET\n");
    bullets.push_back(b);
    //printf("BULLET ADDED\n");

}

void gameEngine::Draw() {


    //Clear the Screen
    SDL_RenderClear(gameRender);

    //Load the Background image to the render Window last
    int iW, iH;
    SDL_QueryTexture(gameBackground, NULL, NULL, &iW, &iH);
    int x = WINDOW_WIDTH / 2 - iW / 2;
    int y = WINDOW_HEIGHT / 2 - iH / 2;

    //Draw the image
    RenderTexture(gameBackground, gameRender, x, y);


    if ( this->gameState == PLAYING) {

        if (gameReady) {
           // currentPlayer->sprite->Draw(gameRender,currentPlayer->pos->x, currentPlayer->pos->y);
            currentPlayer->Draw(gameRender);


            for(std::vector<Bullet*>::iterator bt = bullets.begin(); bt != bullets.end();) {

                (*bt)->Draw(gameRender);

                if ((*bt)->pos->x > WINDOW_WIDTH) {
                    bt = bullets.erase(bt);

                } else if ((*bt)->pos->y > WINDOW_HEIGHT) {
                    bt = bullets.erase(bt);

                } else {
                    ++bt;

                }

            }

            for(std::vector<Enemy*>::iterator et = enemies.begin(); et != enemies.end();) {

                (*et)->Draw(gameRender);

                if ((*et)->pos->x > WINDOW_WIDTH) {
                    et = enemies.erase(et);

                } else if ((*et)->pos->y > WINDOW_HEIGHT) {
                    et = enemies.erase(et);

                } else {
                    ++et;

                }

            }





            //currentEnemy->Draw(gameRender);
            //Draw Enemies

       }   else {
            std::cout << "GAME NOT READY-> " << std::endl;

        }

    }

    //Update the screen
    SDL_RenderPresent(gameRender);

}
void gameEngine::Cleanup(){

    this->gameState = EXIT;

    SDL_DestroyTexture(gameBackground);

    SDL_DestroyRenderer(gameRender);

    //SDL_FreeSurface(  this->gameBackground );
    this->gameBackground = NULL;

    //Destroy window
    SDL_DestroyWindow( gameWindow );
    this->gameWindow = NULL;


    Mix_CloseAudio();
    // Tell SDL to shutdown and free any resources it was using. //
    IMG_Quit();
    SDL_Quit();


}



void gameEngine::MenuInput() {


    if(InputHandler::getInstance()->keyIsDown(SDL_SCANCODE_ESCAPE)){
        gameState = CLEANUP;
    }

    if(InputHandler::getInstance()->keyIsDown(SDL_SCANCODE_SPACE)){
        gameReady = false;
        currentPlayer = nullptr;
        enemies.clear();
        gameState = PLAYING;
        LoadScreen();
    }
}

void gameEngine::GameInput() {

    if(InputHandler::getInstance()->keyIsDown(SDL_SCANCODE_ESCAPE)){
        gameState = GAME_OVER;
    }
}

void gameEngine::SetGameState(int state) {

    gameEngine::gameState = state;


}

SDL_Texture* gameEngine::getBackground() {

  return gameBackground;
}


float gameEngine::getTimer() {

    float timer = SDL_GetTicks() - gameTimer;

    return  timer;

}

SDL_Surface* gameEngine::getGameSurface () {

    return this->gameSurface;


}
/*
SDL_Window* gameEngine::getWindow() {

    return this->gameWindow;
}


  */
void gameEngine::SetPlayer(std::string playerId) {

    if (currentPlayer == NULL) {
        currentPlayer = new Player();
    }

}