//
// Created by Brett Beers on 1/12/14.
// Copyright (c) 2014 Brett Beers. All rights reserved.
//


#include "Game.h"

#define SIGN(v) ( (v < 0 ? -1 : 1) )

Game* Game::getInstance(){
    if(!Game::_instance)
        Game::_instance = new Game();

    return Game::_instance;
}

int Game::setup(){
    config = Configurator::open("config/game.config");

    windowWidth = atoi((*config)["window_width"].c_str());
    windowHeight = atoi((*config)["window_height"].c_str());

    if(SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        std::cout << "ERROR SDL_Init" << std::endl;
        return -1;
    }

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION,3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION,2);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

    window = SDL_CreateWindow(
            ((*config)["window_title"]).c_str(),             // window title
            SDL_WINDOWPOS_CENTERED,     // x position, centered
            SDL_WINDOWPOS_CENTERED,     // y position, centered
            windowWidth,                // width, in pixels
            windowHeight,               // height, in pixels
            SDL_WINDOW_OPENGL           // flags
    );

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_TARGETTEXTURE | SDL_RENDERER_ACCELERATED);
    glContext = SDL_GL_CreateContext(window);

    glEnable(GL_BLEND);
    glEnable(GL_DEPTH_TEST);

    // setup opengl
    SDL_RendererInfo displayRendererInfo;
    SDL_GetRendererInfo(renderer, &displayRendererInfo);

    if((displayRendererInfo.flags & SDL_RENDERER_ACCELERATED) == 0 &&
            (displayRendererInfo.flags & SDL_RENDERER_TARGETTEXTURE) == 0)
    {
        // TODO: Display error regarding no accelerated surface
        std::cout << "BROKEN!" << std::endl;
        throw 1;
    }

    printf("shader lang: %s\n",glGetString(GL_SHADING_LANGUAGE_VERSION));

    return 0;
}

int Game::run(){

    bool gameRunning = true;

    KeyboardHandler* keyboard = KeyboardHandler::getInstance();


    Camera camera = Camera(glm::vec3(0.0f, 0.0f, 1000.0f), glm::vec3(0, 0, 0));
    SDL_SetRelativeMouseMode((SDL_bool)true);

    glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );

    GLuint VertexArrayID;
    glGenVertexArrays(1, &VertexArrayID);
    glBindVertexArray(VertexArrayID);

    GLuint programID = LoadShaders( "shaders/simpleVertexShader.vs", "shaders/simpleFragmentShader.fs" );
    GLuint MatrixID = glGetUniformLocation(programID, "ProjectionViewModel");
    GLuint ColorID = glGetUniformLocation(programID, "Color");

    // set up the projection
    glm::mat4 Projection = glm::perspective(45.0f, (static_cast<float>(windowWidth)) / (static_cast<float>(windowHeight)), 0.1f, 1000.0f);

    GLuint vertexBuffer;
    glGenBuffers(1, &vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, (36*3)*sizeof(GLfloat), CubeTile::cubeCoords, GL_STATIC_DRAW);

    glVertexAttribPointer(
            0,                  // attribute. No particular reason for 0, but must match the layout in the shader.
            3,                  // size
            GL_FLOAT,           // type
            GL_FALSE,           // normalized?
            0,  // stride
            (void*)0            // array buffer offset
    );

    // let the mouse be moved to the center.
    keyboard->updateMouse();

    float FrameCounter = 0.0f;
    float SDLTimeOffset = SDL_GetTicks();

    while(gameRunning)
    {
        SDL_Event event;
        while(SDL_PollEvent(&event))
        {
            keyboard->update(event);
        }
        keyboard->updateMouse();

        if(keyboard->keyDown(SDL_SCANCODE_Q))
            gameRunning = false;

        // ---------- UPDATE ------------


        camera.update();

        // Model matrix : an identity matrix (model will be at the origin)
        glm::mat4 Model = glm::mat4();
        glm::mat4 View = camera.getViewMatrix();

        glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

        int ErrorCheckValue = glGetError();

        glUseProgram(programID);

        ErrorCheckValue = glGetError();

        glEnableVertexAttribArray(0);

        ErrorCheckValue = glGetError();

        const float cubes = 10.0f;

        for(int k = 0; k < cubes; k++)
        for(int j = 0; j < cubes; j++)
        for(int i = 0; i < cubes; i++)
        {
//            glm::mat4 MVP = Projection * View * glm::translate(Model, glm::vec3(2.0f*i, 2.0f*k, 2.0f*j));
//            glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);
//            glUniform3fv(ColorID, 1, glm::value_ptr(glm::vec3((i/cubes), (j/cubes), (k/cubes)) ));
//
//            // Draw the triangle !
//            glDrawArrays(GL_TRIANGLES, 0, 12*3);
        }

        glDisableVertexAttribArray(0);

        std::cout << ++FrameCounter/((SDL_GetTicks() - SDLTimeOffset)/1000) << std::endl;

        SDL_GL_SwapWindow(window);
    }

    return 0;
}
int Game::cleanup(){
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_GL_DeleteContext(glContext);

    SDL_Quit();

    return 0;
}

Game::~Game(){
    if(window)
        delete window;
    window = nullptr;
}

//******************************************
// Private
//******************************************

// static
Game* Game::_instance = nullptr;

Game::Game(){
    window = nullptr;
}

Game::Game(Game& g){

}


