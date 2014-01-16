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
            gameBackground = LoadTexture("welcome.jpg");
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
   // if (currentPlayer == nullptr) {
        printf( "CREATE PLAYER\n" );
        currentPlayer = new Player();
    currentPlayer->pos->x = 100;
    currentPlayer->pos->y = 100;
        gameInit = currentPlayer->Spawn();
    //}

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

            this->Update(event);

            this->Draw();

            gameTimer = SDL_GetTicks();

        }

        if (gameState == CLEANUP) {

            Cleanup();

        }

    }



}


void gameEngine::Update(SDL_Event &event) {



    switch(gameState) {

        case SETUP:

            //this->loadStateResources( this->currentGameState);
            break;

        case MENU:
            //Load the Welcome screen

            this->MenuInput(event);

            break;

        case PLAYING:

            this->GameInput(event);
//            currentPlayer->HandleInput(event);

            //Update the Player
            currentPlayer->Update();

            //Update the Monsters

            //Update the Bullets

            //General Game input handler

            break;

        case GAME_OVER:

            this->MenuInput(event);
            break;

        default:
            break;



    }

    Draw();



}


void gameEngine::Draw() {


    //Clear the Screen
    SDL_RenderClear(gameRender);
    /*
    gameBackground = LoadTexture("welcome.jpg", gameRender);
    //Apply the image
    SDL_BlitSurface(  gameBackground, NULL,  gameSurface, NULL );

    //Update the surface
    SDL_UpdateWindowSurface(  gameWindow );
      */

    //Loads the current level texture background as gameBackground


    //Load the Background image to the render Window last
    int iW, iH;
    SDL_QueryTexture(gameBackground, NULL, NULL, &iW, &iH);
    int x = WINDOW_WIDTH / 2 - iW / 2;
    int y = WINDOW_HEIGHT / 2 - iH / 2;

    //Draw the image
    RenderTexture(gameBackground, gameRender, x, y);


    if ( this->gameState == PLAYING) {
        //std::cout << "SHOULD GO DRAW PLAYER-> " << std::endl;
        //Draw Player

        //if (currentPlayer->image == nullptr) {
        //  printf( "IMAGE IS NULL:\n");
        // currentPlayer->image = LoadTexture("player.png");

        //}

        //image = LoadTexture("player.png");
        //RenderTexture( LoadTexture("player.png"), gameRender, 300, 400);
        //RenderTexture(currentPlayer->image, gameRender, 300, 400);


        //image = gEngine->LoadTexture("player.png");
        if (gameReady) {
            currentPlayer->Draw(gameRender);
        }   else {
            std::cout << "GAME NOT READY-> " << std::endl;

        }


        //Draw Enemies
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



void gameEngine::MenuInput(SDL_Event &event) {


    //User requests quit
    if( event.type == SDL_KEYDOWN ) {
        //std::cout << "KEY = " <<  event.key.keysym.sym << std::endl;
       //std::cout << "SPACE KEY = " <<  SDLK_SPACE << std::endl;
        //Select surfaces based on key press
        switch( event.key.keysym.sym ) {
            case SDLK_ESCAPE:
                printf( "MENU ESCAPE\n" );

                gameState = CLEANUP;

                break;
            case SDLK_UP:
                printf( "PLAY GAME\n" );

                gameState = PLAYING;
                LoadScreen();
                break;
            case SDLK_DOWN:
                printf( "KEY DOWN Menu\n" );
                break;

            case SDLK_p:
                printf( "P KEY\n" );

                gameState = PLAYING;

                break;

        }
    }


}

void gameEngine::GameInput(SDL_Event &event) {


    //User requests quit
    if( event.type == SDL_KEYDOWN ) {
        //std::cout << "KEY = " <<  event.key.keysym.sym << std::endl;
        //std::cout << "SPACE KEY = " <<  SDLK_SPACE << std::endl;
        //Select surfaces based on key press
        switch( event.key.keysym.sym ) {
            case SDLK_ESCAPE:
                printf( "GAME ESCAPE\n" );

                gameState = CLEANUP;

                break;

        }

    }


};


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