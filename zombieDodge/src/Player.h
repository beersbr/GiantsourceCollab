//
// Created by Matt Jacobs on 1/9/14.
// Copyright (c) 2014 Brett Beers. All rights reserved.
//

#ifndef __PLAYER_H_
#define __PLAYER_H_

#include <iostream>
#include <assert.h>
#include <math.h>

#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>

#include "common.h"

#include "Vector.h"
#include "Size.h"
#include "Entity.h"

class Player : public Entity{
public:
	Player();
    Player(int _x, int _y, int _z, std::string _playerTarget, int _hp);
	~Player();

    void Update(SDL_Event& event);
    void Update(); // because it has to be there
    bool Spawn();
    void Move(SDL_Event& event);
    void Draw();
    void TakeDamage(int dmg);
    void Shoot(int dx, int dy);

public:
	Vector* vel;
	Size<int> size;

	SDL_Texture* image;

    int hitPoints;
	int exp;

    bool isSprinting;
    int nonSprintElapsedTime;
    int sprintSpeed;
    int sprintInterval;
    int lastSprintTime;
    int sprintLength;
    int sprintElapsedTime;
    int moveSpeed;
    int sprintTime;

};

#endif // __PLAYER_H_