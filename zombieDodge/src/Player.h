#ifndef  PLAYER_H
#define PLAYER_H


//
// Created by Matt Jacobs on 1/9/14.
// Copyright (c) 2014 Brett Beers. All rights reserved.
//

#include <iostream>
#include <assert.h>
#include <math.h>

#include "gameEngine.h"
#include "common.h"
#include "Vector.h"
#include "Size.h"
#include "Entity.h"


class Player : public Entity {

public:

    Player();
    Player(int _x=0, int _y=0, int _z=0,std::string playerTarget = std::string(), int _hp=1);
    ~Player();

    Vector pos;
    Vector vel;
    int x,y,z = 0;
    float hitPoints, exp;
    int playerId;
    SDL_Surface *image = NULL;

    //gameEngine* gEngine = gameEngine::getInstance();



   // this.sprite = new Sprite({ image: this.image, frameTime: (1000/60 * 8), frameHeight: GAME.CurrentPlayer.sprite.h, frameWidth: GAME.CurrentPlayer.sprite.w});
    int moveSpeed = 150; // pixels/second
    int sprintSpeed = 300;
    bool isSprinting = false;
    float sprintInterval;
    float sprintTime = 500;
    float sprintLength = 0;
    float lastSprintTime = -1;
    float sprintElapsedTime =0;
    float nonSprintElapsedTime = 0;
    float runBarPercent = 100;

    bool isShooting = false;
    float shootInterval = 250; //ms
    float lastShotTime = -1;
    float lastShotElaspedTime = -1;
    int zombiesKilled = 0;
    int shotsFired = 0;
    float kdRatio = 0;

    int configIndex;
    std::string name;
    std::string playerTarget;

    virtual void Update(SDL_Event& event) = 0;
    virtual void Spawn();
    virtual void TakeDamage(float dmg);

    virtual void Move(SDL_Event& event);
    virtual void Shoot(int x, int y);

    virtual void Draw();
};

#endif



