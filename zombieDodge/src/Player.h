//
// Created by Matt Jacobs on 1/9/14.
// Copyright (c) 2014 Brett Beers. All rights reserved.
//

#include <iostream>
#include <assert.h>
#include <math.h>

#include "Vector.h"
#include "Size.h"
#include "Entity.h"

class Player : public Entity{
public:
	Player();
	~Player();

    void update();
    void spawn();
    void move();
    void draw();
    void takeDamage(int dmg);

public:
	Vector* vel;
	Size<int> size;

    int hitPoints;
	int exp;
};
