//
// Created by Matt Jacobs on 1/9/14.
// Copyright (c) 2014 Brett Beers. All rights reserved.
//

#ifndef __PLAYER_H_
#define __PLAYER_H_
#include <iostream>
#include <iosfwd>
#include <stack>
#include <string>
#include <map>
#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include "Entity.h"
#include "Sprite.h"
#include "Bullet.h"


class Player : public Entity{
public:
	Player();
    Player(float _x, float _y, float _z, std::string _playerTarget, int _hp);
	~Player();


    bool Spawn();
    //void Move();
    void Update(); // because it has to be there
    void Draw(SDL_Renderer *renderer, SDL_Rect *camera);
    void TakeDamage(int dmg);
    void Shoot(int dx, int dy);
    SDL_Rect GetHitBox();
    SDL_Rect hitBox;
	Vector* vel;
	Size<int> size;
    std::string spritePath;
    Sprite* sprite;
    int spriteFrames;
    int spriteRows;
    float hitPoints;
    float exp;
    bool spawned = false;
    std::string playerId;
    bool isSprinting = false;
    float nonSprintElapsedTime = 0;
    float sprintSpeed = 20.0;
    float sprintInterval = 200;
    float lastSprintTime = -1;
    float sprintLength = 0;
    float sprintElapsedTime = 0;
    float moveSpeed = 15.0;
    float sprintTime = 500;
    bool isShooting = false;
    int shotsFired = 0;
    int enemiesKilled = 0;
    float kdRatio = 0.0;
    float lastShotTime= 0.0;
    float shootInterval = 250;
    std::map<std::string, std::string>* config;
    SDL_Rect clip;

};

#endif // __PLAYER_H_