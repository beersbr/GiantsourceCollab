//
// Created by Matt Jacobs on 1/9/14.
// Copyright (c) 2014 Brett Beers. All rights reserved.
//

#ifndef __PLAYER_H_
#define __PLAYER_H_
#include "Entity.h"
#include "Sprite.h"
#include "Bullet.h"
#include <iostream>
#include <iosfwd>
#include <stack>
#include <string>
#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>

class Player : public Entity{
public:
	Player();
    Player(float _x, float _y, float _z, std::string _playerTarget, int _hp);
	~Player();


    bool Spawn();
    //void Move();
    void Update(); // because it has to be there
    void Draw(SDL_Renderer *renderer);
    void TakeDamage(int dmg);
    void Shoot(int dx, int dy);
    SDL_Rect GetHitBox();
    SDL_Rect hitBox;
	Vector* vel;
	Size<int> size;

	SDL_Texture* image;
    Sprite* sprite;
    float hitPoints;
    float exp;
    bool spawned = false;
    std::string playerId;
    bool isSprinting;
    float nonSprintElapsedTime;
    float sprintSpeed;
    float sprintInterval;
    float lastSprintTime;
    float sprintLength;
    float sprintElapsedTime;
    float moveSpeed = 10.0;
    float sprintTime = 15.0;
    int frameCount = 0;
    int bulletCnt = 0;
    //std::map<int, Bullet*> bullets;

    /***** SPRITE STUFF */
    float originX;
    int animationDelay;
    float originY;
     int currentRow;
    int imgWidth;
    int imgHeight;
    int currentFrame;
    int frameEnd;
    int frameBegin;
    int frameX;
    int frameY;

    SDL_Rect clip;


};

#endif // __PLAYER_H_