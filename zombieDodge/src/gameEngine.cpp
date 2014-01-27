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

void gameEngine::Render(SDL_Texture *texture, int x, int y, int h, int w, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip )
{
    //Set rendering space and render to screen
    SDL_Rect renderQuad = { x, y, h, w };

    //Set clip rendering dimensions
    if( clip != NULL )
    {
        renderQuad.w = clip->w;
        renderQuad.h = clip->h;
    }

    //Render to screen
    SDL_RenderCopyEx(gameRender, texture, clip, &renderQuad, angle, center, flip );
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
            gameBackground = LoadTexture("citybg.jpg");
            gameHUD = LoadTexture("HUD.png");
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


void gameEngine::SetColor(SDL_Texture *texture, Uint8 red, Uint8 green, Uint8 blue )
{
    //Modulate texture rgb
    SDL_SetTextureColorMod( texture, red, green, blue );
}

void gameEngine::SetBlendMode(SDL_Texture *texture, SDL_BlendMode blending )
{
    //Set blending function
    SDL_SetTextureBlendMode( texture, blending );
}

void gameEngine::SetAlpha(SDL_Texture *texture, Uint8 alpha )
{
    //Modulate texture alpha
    SDL_SetTextureAlphaMod( texture, alpha );
}


bool gameEngine::LoadText( std::string textureText, SDL_Color textColor )
{
    //Get rid of preexisting texture
   if (gameText != NULL) {
       SDL_DestroyTexture( gameText );
       gameText = NULL;
       textWidth = 0;
       textHeight = 0;


   }

    //Render text surface
    SDL_Surface* textSurface = TTF_RenderText_Solid( gameFont, textureText.c_str(), textColor );
    if( textSurface == NULL )
    {
        printf( "Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError() );
    }
    else
    {
        //Create texture from surface pixels
        gameText = SDL_CreateTextureFromSurface(gameRender, textSurface );
        if( gameText == NULL )
        {
            printf( "Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError() );
        }
        else
        {
            //Get image dimensions
            textWidth = textSurface->w;
            textHeight = textSurface->h;
        }

        //Get rid of old surface
        SDL_FreeSurface( textSurface );
    }

    //Return success
    return gameText != NULL;
}


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

   // config = Configurator::open("config/game.config");

    gameConfig = new Jsonator();
    gameConfig->LoadData("config/config.json");

    windowWidth = gameConfig->GetInt("settings","width",NULL);
    windowHeight = gameConfig->GetInt("settings","height",NULL);
    //std::cout << "QINDO QWIDTH  -> " << WINDOW_HEIGHT << std::endl;
    //printf("CAMERA SET");
    camera.x =0;
    camera.y=0;
    camera.w = windowWidth;
    camera.h = windowHeight;
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
                gameConfig->GetString("settings","title",NULL).c_str(),             // window title
                SDL_WINDOWPOS_CENTERED,     // x position, centered
                SDL_WINDOWPOS_CENTERED,     // y position, centered
                windowWidth,                        // width, in pixels
                windowHeight,                        // height, in pixels
                NULL
        );
        if( gameWindow == NULL )
        {
            printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
            success = false;
        }
        else
        {

            //Enable VSync
            if( !SDL_SetHint( SDL_HINT_RENDER_VSYNC, "1" ) )
            {
                printf( "Warning: VSync not enabled!" );
            }

            //Set texture filtering to linear
            if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
            {
                printf( "Warning: Linear texture filtering not enabled!" );
            }

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
            //Initialize SDL_ttf
            if( TTF_Init() == -1 )
            {
                printf( "SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError() );
                success = false;
            }   else {

               gameFont = TTF_OpenFont( "Arial.ttf", 28 );

            }

            //Initialize SDL_mixer
            if( Mix_OpenAudio( 22050, MIX_DEFAULT_FORMAT, 2, 4096 ) == -1 )
            {
                success = false;
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

   // printf("GO SET UP");
    while ( this->gameState != EXIT) {

        if (getTimer() >= FRAME_RATE )
        {
            SDL_Event event;
            while( SDL_PollEvent( &event ) != 0 ){
                SDL_GetMouseState( &mouseX, &mouseY);

                switch(event.type)
                {
                    case SDL_KEYDOWN:
                        InputHandler::getInstance()->keyDown(event.key.keysym.scancode);
                        break;
                    case SDL_KEYUP:
                        InputHandler::getInstance()->keyUp(event.key.keysym.scancode);
                        break;
                    case SDL_MOUSEMOTION:
                       // InputHandler::getInstance()->mouseButtonUp(event.button);
                        break;
                    case SDL_MOUSEBUTTONDOWN:
                        if (event.button.button == SDL_BUTTON_LEFT) {
                            //std::cout << "LEFT DOWN  -> " << event.button.x << std::endl;
                            InputHandler::getInstance()->mouseButtonDown();
                        }

                        //InputHandler::getInstance()->setMouseXY(mouseX, mouseY);
                        //InputHandler::getInstance()->mouseButtonDown(1);
                       break;
                    case SDL_MOUSEBUTTONUP:
                        InputHandler::getInstance()->mouseButtonUp();

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
                 break;
                case GAME_OVER:
                    camera.x =0;
                    camera.y=0;
                    camera.w = windowWidth;
                    camera.h = windowHeight;
                    //textColor = { 255, 255, 255 };
                    //LoadText("You Have Lost", textColor);

                  break;

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
                if (currentPlayer->spawned) {
                    currentPlayer->Update();
                }
                camera.x = ( currentPlayer->pos->x + currentPlayer->clip.w / 2 ) - windowWidth / 2;
                camera.y = ( currentPlayer->pos->y + currentPlayer->clip.h / 2 ) - windowHeight / 2;

                //Keep the camera in bounds
                if( camera.x < 0 )
                {
                    camera.x = 0;
                }
                if( camera.y < 0 )
                {
                    camera.y = 0;
                }
                if( camera.x > levelWidth - camera.w )
                {
                    camera.x = levelWidth - camera.w;
                }
                if( camera.y > levelHeight - camera.h )
                {
                    camera.y = levelHeight - camera.h;
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
                        e = nullptr;
                        enemyCnt = 0;
                }
                enemyCnt++;

                std::cout << enemies.size() << std::endl;

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
                              bt = bullets.erase(bt);
                              bt = bullets.end();

                        }  else {
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

    bullets.push_back(b);

}

void gameEngine::Draw() {

    //Clear the Screen
    SDL_RenderClear(gameRender);

    //Load the Background image to the render Window last
    //int iW, iH;
    //SDL_QueryTexture(gameBackground, NULL, NULL, &iW, &iH);
    //int x = WINDOW_WIDTH / 2 - iW / 2;
    //int y = WINDOW_HEIGHT / 2 - iH / 2;

    //Draw the image
   // RenderTexture(gameBackground, gameRender, x, y);
    Render(gameBackground, 0, 0, windowWidth, windowHeight, &camera, NULL, NULL, SDL_FLIP_NONE);

    if ( this->gameState == PLAYING) {

        if (gameReady) {

            currentPlayer->Draw(gameRender,&camera);

            for(std::vector<Bullet*>::iterator bt = bullets.begin(); bt != bullets.end();) {

                (*bt)->Draw(gameRender, &camera);

                if ((*bt)->pos->x > levelWidth) {
                    bt = bullets.erase(bt);

                } else if ((*bt)->pos->y > levelHeight) {
                    bt = bullets.erase(bt);

                } else {
                    ++bt;

                }

            }

            for(std::vector<Enemy*>::iterator et = enemies.begin(); et != enemies.end();) {

                (*et)->Draw(gameRender,&camera);

                if ((*et)->pos->x > levelWidth) {
                    et = enemies.erase(et);

                } else if ((*et)->pos->y > levelHeight) {
                    et = enemies.erase(et);

                } else {
                    ++et;

                }

            }

            //SDL_QueryTexture(gameHUD, NULL, NULL, &iW, &iH);
            //x = WINDOW_WIDTH / 2 - iW / 2;
            //y = WINDOW_HEIGHT / 2 - iH / 2;

            //Draw the HUD SCREEN
            RenderTexture(gameHUD, gameRender, 0, 0);

       }   else {
            std::cout << "GAME NOT READY-> " << std::endl;

        }

    } else if (gameState == GAME_OVER){

        //Render(gameText, 300, 200, 400, 50, NULL, NULL, NULL, SDL_FLIP_NONE);

    }

    //Update the screen
    SDL_RenderPresent(gameRender);

}
void gameEngine::Cleanup(){

    SDL_DestroyTexture(gameBackground);

    SDL_DestroyTexture(gameHUD);

    SDL_DestroyRenderer(gameRender);

    //Destroy window
    SDL_DestroyWindow( gameWindow );

    this->gameWindow = NULL;

    Mix_CloseAudio();
    // Tell SDL to shutdown and free any resources it was using. //
    IMG_Quit();
    SDL_Quit();

    gameState = EXIT;

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