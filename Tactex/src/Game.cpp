//
// Created by Brett Beers on 1/12/14.
// Copyright (c) 2014 Brett Beers. All rights reserved.
//


#include "Game.h"

Game* Game::getInstance(){
    if(!Game::_instance)
        Game::_instance = new Game();

    return Game::_instance;
}

int Game::setup(){
    if(SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        std::cout << "ERROR SDL_Init" << std::endl;
        return -1;
    }

    window = SDL_CreateWindow(
            "SDL 2 window",             // window title
            SDL_WINDOWPOS_CENTERED,     // x position, centered
            SDL_WINDOWPOS_CENTERED,     // y position, centered
            800,                        // width, in pixels
            600,                        // height, in pixels
            SDL_WINDOW_OPENGL           // flags
    );

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_TARGETTEXTURE | SDL_RENDERER_ACCELERATED);

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION,3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION,2);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

    glContext = SDL_GL_CreateContext(window);

    // setup opengl

    SDL_RendererInfo displayRendererInfo;
    SDL_GetRendererInfo(renderer, &displayRendererInfo);

    if(displayRendererInfo.flags & SDL_RENDERER_ACCELERATED == 0 &&
            displayRendererInfo.flags & SDL_RENDERER_TARGETTEXTURE == 0)
    {
        // TODO: Display error regarding no accelerated surface
        std::cout << "BROKEN!" << std::endl;
        throw 1;
    }

    glShadeModel(GL_SMOOTH);
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClearDepth(1.0f);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_EQUAL);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

    // setup the viewport

    int width = 800, height = 600;

    if(height == 1)
        height = 1;

    GLfloat ratio = (GLfloat)width/(GLfloat)height;
    glViewport(0, 0, (GLsizei)width, (GLsizei)height);
    glMatrixMode(GL_PROJECTION);

    glLoadIdentity();

    gluPerspective(45.0f, ratio, 0.1f, 100.0f);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    printf("shader lang: %s\n",glGetString(GL_SHADING_LANGUAGE_VERSION));

    return 0;
}

int Game::run(){

    bool gameRunning = true;

    KeyboardHandler* keyboard = KeyboardHandler::getInstance();

    while(gameRunning)
    {
        keyboard->update();

        if(keyboard->keyDown(SDL_SCANCODE_Q))
            gameRunning = false;

        // render some stuff

        glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );
        glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

        GLuint VertexArrayID;
        glGenVertexArrays(1, &VertexArrayID);
        glBindVertexArray(VertexArrayID);

        GLuint programID = LoadShaders( "shaders/simpleVertexShader.fs", "shaders/simpleFragmentShader.fs" );



        static const GLfloat g_vertex_buffer_data[] = {
                -1.0f, -1.0f, 0.0f,
                1.0f, -1.0f, 0.0f,
                0.0f,  1.0f, 0.0f,
        };

        GLuint vertexbuffer;

        // Generate 1 buffer, put the resulting identifier in vertexbuffer
        glGenBuffers(1, &vertexbuffer);

        // The following commands will talk about our 'vertexbuffer' buffer
        glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);

        // Give our vertices to OpenGL.
        glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

        glDrawArrays(GL_TRIANGLES, 0, 3); // Starting from vertex 0; 3 vertices total -> 1 triangle
        glDisableVertexAttribArray(0);

        // do something with the

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


