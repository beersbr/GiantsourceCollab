#import "gameEngine.h"

gameEngine* gameEngine::_instance = nullptr;

gameEngine* gameEngine::getInstance() {

    if (!gameEngine::_instance)
        gameEngine::_instance = new gameEngine();

    return gameEngine::_instance;

}

SDL_Event gameEngine::getEvent() {

    SDL_Event gameEvent;
    SDL_PollEvent( &gameEvent );

    return gameEvent;

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

void gameEngine::logSDLError(std::ostream &os, const std::string &msg){
    os << msg << " error: " << SDL_GetError() << std::endl;
}

void gameEngine::ApplySurface(float x, float y, SDL_Texture *source, SDL_Renderer *destination)
{
    SDL_Rect pos;
    pos.x = x;
    pos.y = y;
    SDL_QueryTexture(source, NULL, NULL, &pos.w, &pos.h);
    SDL_RenderCopy(destination, source, NULL, &pos);

}
SDL_Texture* gameEngine::LoadTexture(const std::string &file, SDL_Renderer *ren){
    SDL_Texture *texture = IMG_LoadTexture(ren, file.c_str());
    if (texture == nullptr)
        printf( "Failed to load  texture!\n %s:", file.c_str() );
    return texture;
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

void gameEngine::RenderTexture(SDL_Texture *tex, int x, int y){
    int w, h;
    //printf( "RENDER THE PLAYER TEXTURE!\n" );
    SDL_QueryTexture(tex, NULL, NULL, &w, &h);
    RenderTexture(tex, gameRender, x, y, w, h);
}

bool gameEngine::LoadScreen()
{

    //std::cout << "LOAD BACKGROUND FOR  = " <<  gameState << std::endl;

    //Loading success flag
    bool success = true;

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


    //Once a config is in place, grab all the user data from the config and create the new player that way,
    //Config playerConfig = getConfig(_playerTarget);
    if (currentPlayer == nullptr) {
        printf( "CREATE PLAYER\n" );
        currentPlayer = new Player();
        currentPlayer->pos->x = 100;
        currentPlayer->pos->y = 100;
        gameInit = currentPlayer->Spawn();

        currentEnemy = new Enemy();
        currentEnemy->Spawn();
        enemies[0] = currentEnemy;


    }

    //Also set initial game state object

    return gameInit;

}
bool gameEngine::Setup(){

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
                WINDOW_CAPTION.c_str(),             // window title
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
                currentPlayer->Update();
                std::cout << "------------------------------enemyCnt  " <<   enemyCnt << std::endl;
                //if (static_cast<float>(rand() % static_cast<int>(gameTimer + 1))< gameTimer * 0.05) {
                   if (enemyCnt> 40) {
                       std::cout << "------------------------------SPAWN ANOTHER ENEMY  " <<   std::endl;

                        totalEnemyCnt++;
                        std::string enemyType;

                        Enemy *enemy = new Enemy();
                        enemy->Spawn();

                        enemies[totalEnemyCnt] = enemy;
                       enemyCnt = 0;
                   }

                enemyCnt++;
               // }

                for (auto e=enemies.begin(); e!=enemies.end(); ++e)  {

                    e->second->Update();

                    if((CheckCollision(e->second->GetHitBox(), currentPlayer->GetHitBox() ) ))
                    {
                        printf("GAMEOVER");
                        gameState = GAME_OVER;
                    }


                }


                //currentEnemy->Update();
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
            currentPlayer->Draw(gameRender);

            for (auto e=enemies.begin(); e!=enemies.end(); ++e)  {

                e->second->Draw(gameRender);
                /*
                if (e->second->pos->x > WINDOW_WIDTH) {
                    enemies.erase (e->first);

                } else if (e->second->pos->y > WINDOW_HEIGHT) {
                    enemies.erase (e->first);
                }
                  */
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