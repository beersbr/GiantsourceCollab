//
// Created by Matt Jacobs on 1/9/14.
// Copyright (c) 2014 Brett Beers. All rights reserved.
//

#ifndef __PLAYER_H_
#define __PLAYER_H_
#include "Entity.h"
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>

class Player : public Entity{
public:
	Player();
    Player(int _x, int _y, int _z, std::string _playerTarget, int _hp);
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

    float hitPoints;
    float exp;
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

};

#endif // __PLAYER_H_