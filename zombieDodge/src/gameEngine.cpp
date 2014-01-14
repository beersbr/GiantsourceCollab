#import "gameEngine.h"
#import "config.h"
#import "Player.h"

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


SDL_Surface* gameEngine::LoadImage( const std::string& path )
{
    //The image that's loaded
    SDL_Surface* loadedImage = NULL;

    //The optimized surface that will be used
    SDL_Surface* optimizedImage = NULL;

    //Load the image
    loadedImage = IMG_Load( path.c_str() );

    //If the image loaded
    if( loadedImage != NULL )
    {
        //Create an optimized surface
        optimizedImage = SDL_ConvertSurfaceFormat( loadedImage, SDL_PIXELTYPE_UNKNOWN,NULL);

        //Free the old surface
        SDL_FreeSurface( loadedImage );

        //If the surface was optimized
        if( optimizedImage != NULL )
        {
            //Color key surface
            SDL_SetColorKey( optimizedImage, SDL_TRUE, SDL_MapRGB( optimizedImage->format, 0, 0xFF, 0xFF ) );
        }
    }

    //Return the optimized surface
    return optimizedImage;
}

void gameEngine::ApplySurface( int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip)
{
    //Holds offsets
    SDL_Rect offset;

    //Get offsets
    offset.x = x;
    offset.y = y;

    //Blit
    SDL_BlitSurface( source, clip, destination, &offset );
}


bool gameEngine::Setup(){

    this->gameState = SETUP;
    //Initialization flag
    bool success = true;

    this->gameTimer = SDL_GetTicks();

    //Initialize SDL
    if( SDL_Init( SDL_INIT_EVERYTHING ) < 0 )
    {
        printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
        success = false;
    }
    else
    {
        //Create window
        this->gameWindow = SDL_CreateWindow(
                WINDOW_CAPTION.c_str(),             // window title
                SDL_WINDOWPOS_CENTERED,     // x position, centered
                SDL_WINDOWPOS_CENTERED,     // y position, centered
                WINDOW_WIDTH,                        // width, in pixels
                WINDOW_HEIGHT,                        // height, in pixels
                SDL_WINDOW_OPENGL           // flags
        );
        if( gameEngine::getWindow() == NULL )
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
                //Get window surface
                this->gameSurface = SDL_GetWindowSurface( gameEngine::getWindow());
            }
        }
    }

    return success;

}

bool gameEngine::GameInit () {

    bool gameInit = true;

    printf( "GAME INIT\n" );


    //Once a config is in place, grab all the user data from the config and create the new player that way,
    //Config playerConfig = getConfig(_playerTarget);
    if (currentPlayer == nullptr) {
        printf( "CREATE PLAYER\n" );
        currentPlayer = new Player(300,200,0,'player1',1);

    }

    //Also set initial game state object

    return gameInit;

}

float gameEngine::getTimer() {

    float timer = SDL_GetTicks() - gameEngine::gameTimer;

    return  timer;

}

SDL_Surface* gameEngine::getGameSurface () {

    return this->gameSurface;


}

SDL_Window* gameEngine::getWindow() {

    return this->gameWindow;
}



void gameEngine::SetPlayer(std::string playerId) {

    if (currentPlayer == NULL) {
        currentPlayer = new Player();
    }

}
void gameEngine::Update(SDL_Event &event) {



    switch( this->currentGameState) {


        case -1:
            //Load the Welcome screen
            this->loadStateResources( this->currentGameState);
            break;

        case 0:
            //Load the Welcome screen
            loadScreen(this->currentGameState);
            this->menuInput(event);
            break;

        case 1:
            //Load the Game Level

            //Fill the screen white
            SDL_FillRect( this->gameSurface, &this->gameSurface->clip_rect, SDL_MapRGB( this->gameSurface->format, 0xFF, 0xFF, 0xFF ) );

            currentPlayer->Update(event);
            currentPlayer->Draw();

            this->gameInput(event);
            break;

        default:
            break;



    }



}


void gameEngine::Draw() {



    //Apply the image
    SDL_BlitSurface(  this->gameBackground, NULL,  this->gameSurface, NULL );

    //Update the surface
    SDL_UpdateWindowSurface(  this->gameWindow );



}

void gameEngine::Run() {

    while ( this->gameState != EXIT) {

        if (getTimer() >= FRAME_RATE )
        {



            SDL_Event event;
            while( SDL_PollEvent( &event ) != 0 ){
                if( event.type == SDL_KEYDOWN ) {
                    std::cout << "CODE = " <<  event.key.keysym.sym << std::endl;
                    //Select surfaces based on key press
                    switch( event.key.keysym.sym ) {

                        default:
                            break;

                    }

                }

                else
                if( event.type == SDL_QUIT )
                {

                    this->gameState = CLEANUP;

                }
            }

            if (this->gameState != CLEANUP) {

                if ((this->gameState == PLAYING) && (!gameReady)){

                    gameReady = gameEngine::GameInit();

                    //Move to gamestates
                    this->Update(event);


                    this->Draw();
                }

                this->gameTimer = SDL_GetTicks();
            }
        }
    }
    if (this->gameState == GAME_OVER) {

        this->gameState = CLEANUP;


    } else
    if (this->gameState == EXIT) {

        this->gameState = CLEANUP;


    }

}

void gameEngine::Cleanup(){

    this->gameState = CLEANUP;

    SDL_FreeSurface(  this->gameBackground );
    this->gameBackground = NULL;

    //Destroy window
    SDL_DestroyWindow( gameWindow );
    this->gameWindow = NULL;

    // Tell SDL to shutdown and free any resources it was using. //
    SDL_Quit();

}


bool gameEngine::loadScreen(int screenId)
{
    //Loading success flag
    bool success = true;

    switch(screenId)

    {
        case 0:
            this->gameBackground = LoadImage( "welcome.jpg" );
            break;
        default:
            break;

    }


    if( this->gameBackground == NULL )
    {
        printf( "Failed to load  image!\n" );
        success = false;
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


void gameEngine::menuInput(SDL_Event &event) {


    //User requests quit
    if( event.type == SDL_KEYDOWN ) {
        std::cout << "CODE = " <<  event.key.keysym.sym << std::endl;
        //Select surfaces based on key press
        switch( event.key.keysym.sym ) {
            case SDLK_ESCAPE:
                printf( "ESCAPE\n" );

                this->gameState = CLEANUP;

                break;
            case SDLK_UP:
                printf( "KEY UP Menu\n" );
                //this->currentGameState = 1;
                break;
            case SDLK_DOWN:
                printf( "KEY DOWN Menu\n" );
                break;

            case SDLK_SPACE:
                this->gameState = PLAYING;
                break;

        }
    }


}

void gameEngine::gameInput(SDL_Event &event) {


    switch(event.key.keysym.sym ) {

        case SDLK_UP:
            printf( "KEY UP\n" );
            break;
        case SDLK_DOWN:
            printf( "KEY DOWN\n" );
            break;

    }

};


void gameEngine::SetGameState(int state) {

    gameEngine::gameState = state;


}

SDL_Surface* gameEngine::getBackground() {

  return gameBackground;
}