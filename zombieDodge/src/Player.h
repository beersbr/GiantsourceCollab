//
// Created by Matt Jacobs on 1/9/14.
// Copyright (c) 2014 Brett Beers. All rights reserved.
//

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
	~Player();

    void Update();
    void Spawn();
    void Move();
    void Draw();
    void TakeDamage(int dmg);

public:
	Vector* vel;
	Size<int> size;

	SDL_Surface* image;

    int hitPoints;
	int exp;
};
