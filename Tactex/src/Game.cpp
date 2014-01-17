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
    std::map<std::string, std::string>* config = Configurator::open("config/game.config");

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

    int width = atoi((*config)["window_width"].c_str());
    int height = atoi((*config)["window_height"].c_str());

    window = SDL_CreateWindow(
            ((*config)["window_title"]).c_str(),             // window title
            SDL_WINDOWPOS_CENTERED,     // x position, centered
            SDL_WINDOWPOS_CENTERED,     // y position, centered
            width,                        // width, in pixels
            height,                        // height, in pixels
            SDL_WINDOW_OPENGL           // flags
    );

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_TARGETTEXTURE | SDL_RENDERER_ACCELERATED);
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

    if(height == 1)
        height = 1;

    printf("shader lang: %s\n",glGetString(GL_SHADING_LANGUAGE_VERSION));

    return 0;
}

int Game::run(){

    bool gameRunning = true;

    KeyboardHandler* keyboard = KeyboardHandler::getInstance();

    glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );

    GLuint VertexArrayID;
    glGenVertexArrays(1, &VertexArrayID);
    glBindVertexArray(VertexArrayID);

    GLuint programID = LoadShaders( "shaders/simpleVertexShader.vs", "shaders/simpleFragmentShader.fs" );

    GLuint MatrixID = glGetUniformLocation(programID, "MVP");
    GLuint OffsetID = glGetUniformLocation(programID, "offset");
    glm::mat4 Projection = glm::perspective(45.0f, 4.0f / 3.0f, 0.1f, 1000.0f);

    glm::mat4 View = glm::lookAt(
            glm::vec3(0,0,10), // Camera is at (4,3,3), in World Space
            glm::vec3(0,0,0), // and looks at the origin
            glm::vec3(0,1,0)  // Head is up (set to 0,-1,0 to look upside-down)
    );

    // Model matrix : an identity matrix (model will be at the origin)
    glm::mat4 Model = glm::mat4(1.0f);
    glm::mat4 MVP = Projection * View * Model;

    static const GLfloat g_vertex_buffer_data[] = {

            // west
            -1.0f, -1.0f, -1.0f,
            -1.0f, -1.0f,  1.0f,
            -1.0f,  1.0f,  1.0f,

            -1.0f, -1.0f, -1.0f,
            -1.0f,  1.0f,  1.0f,
            -1.0f,  1.0f, -1.0f,

            // bottom
             1.0f, -1.0f,  1.0f,
            -1.0f, -1.0f,  1.0f,
            -1.0f, -1.0f, -1.0f,

             1.0f, -1.0f,  1.0f,
            -1.0f, -1.0f, -1.0f,
             1.0f, -1.0f, -1.0f,

            // back
             1.0f,  1.0f, -1.0f,
            -1.0f, -1.0f, -1.0f,
            -1.0f,  1.0f, -1.0f,

             1.0f,  1.0f, -1.0f,
             1.0f, -1.0f, -1.0f,
            -1.0f, -1.0f, -1.0f,

            // front
            -1.0f,  1.0f,  1.0f,
            -1.0f, -1.0f,  1.0f,
             1.0f, -1.0f,  1.0f,

             1.0f,  1.0f,  1.0f,
            -1.0f,  1.0f,  1.0f,
             1.0f, -1.0f,  1.0f,

            // right
             1.0f,  1.0f,  1.0f,
             1.0f, -1.0f, -1.0f,
             1.0f,  1.0f, -1.0f,

             1.0f, -1.0f, -1.0f,
             1.0f,  1.0f,  1.0f,
             1.0f, -1.0f,  1.0f,

            // top
             1.0f,  1.0f,  1.0f,
             1.0f,  1.0f, -1.0f,
            -1.0f,  1.0f, -1.0f,

             1.0f,  1.0f,  1.0f,
            -1.0f,  1.0f, -1.0f,
            -1.0f,  1.0f,  1.0f,


    };
    static const GLushort g_element_buffer_data[] = { 0, 1, 2 };

    GLuint vertexbuffer;
    glGenBuffers(1, &vertexbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

    glm::vec3 cameraPos = glm::vec3(0, 0, 10);
    glm::vec3 cameraLookAt = glm::vec3(0, 0, 0);

    // cuz I can
    struct{
        int x, y;
    } typedef MousePos;

    MousePos mousePos;

    SDL_SetRelativeMouseMode((SDL_bool)true);

    SDL_GetRelativeMouseState(&mousePos.x,&mousePos.y);
    while(gameRunning)
    {
        SDL_Event event;
        while(SDL_PollEvent(&event))
        {
            keyboard->update(event);
        }
        SDL_GetRelativeMouseState(&mousePos.x,&mousePos.y);

        if(keyboard->keyDown(SDL_SCANCODE_Q))
            gameRunning = false;

        if(mousePos.x != 0 and mousePos.y != 0)
        {
            if(mousePos.x != 0)
            {
                glm::vec3 base = cameraLookAt - cameraPos;
                base = glm::rotateY(base, -1*(mousePos.x/10.0f));
                cameraLookAt = cameraPos + base;
            }
            if(mousePos.y != 0)
            {
                glm::vec3 base = cameraLookAt - cameraPos;
                glm::vec3 axis = glm::rotateY(base, 90.0f);

                axis = glm::normalize(axis);
                glm::vec3 offset = glm::rotate(base, (float)mousePos.y/10, axis);
                glm::vec3 adder = offset - base;
                cameraLookAt += adder;
            }
        }

        if(keyboard->keyDown(SDL_SCANCODE_A))
        {
            glm::vec3 rot90 = (cameraLookAt - cameraPos);
            rot90[1] = 0.0f;
            rot90 = glm::rotateY(rot90, 90.0f);

            rot90 = glm::normalize(rot90);
            cameraLookAt += rot90;
            cameraPos += rot90;
        }
        if(keyboard->keyDown(SDL_SCANCODE_D))
        {
            glm::vec3 rot90 = (cameraLookAt - cameraPos);
            rot90[1] = 0.0f;
            rot90 = glm::rotateY(rot90, 90.0f);

            rot90 = glm::normalize(rot90);
            cameraLookAt -= rot90;
            cameraPos -= rot90;
        }
        if(keyboard->keyDown(SDL_SCANCODE_W))
        {
            glm::vec3 offset = cameraLookAt - cameraPos;
            offset = glm::normalize(offset);

            cameraLookAt += offset;
            cameraPos += offset;
        }
        if(keyboard->keyDown(SDL_SCANCODE_S))
        {
            glm::vec3 offset = cameraLookAt - cameraPos;
            offset = glm::normalize(offset);

            cameraLookAt -= offset;
            cameraPos -= offset;
        }


        glm::mat4 View = glm::lookAt(
                cameraPos, // Camera is at (4,3,3), in World Space
                cameraLookAt, // and looks at the origin
                glm::vec3(0,1,0)  // Head is up (set to 0,-1,0 to look upside-down)
        );

        // Model matrix : an identity matrix (model will be at the origin)
        glm::mat4 Model = glm::mat4(1.0f);


        glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

        for(int k = -6; k < 6; k++)
        for(int j = -6; j < 6; j++)
        for(int i = -6; i < 6; i++)
        {
            glm::mat4 MVP = Projection * View * glm::translate(Model, glm::vec3(3.0f*i, 3.0f*k, 3.0f*j));

            glUseProgram(programID);
            glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);
            glUniform1f(OffsetID, (float)i);

            glEnableVertexAttribArray(0);
            glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
            glVertexAttribPointer(
                    0,                  // attribute. No particular reason for 0, but must match the layout in the shader.
                    3,                  // size
                    GL_FLOAT,           // type
                    GL_FALSE,           // normalized?
                    0,                  // stride
                    (void*)0            // array buffer offset
            );

            // Draw the triangle !
            glDrawArrays(GL_TRIANGLES, 0, 12*3); // 3 indices starting at 0 -> 1 triangle

            glDisableVertexAttribArray(0);
        }



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


