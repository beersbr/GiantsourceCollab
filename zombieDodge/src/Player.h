//
// Created by Matt Jacobs on 1/9/14.
// Copyright (c) 2014 Brett Beers. All rights reserved.
//

#include <iostream>
#include <assert.h>
#include <math.h>

class Player {
public:


    static void update();
    static void spawn();
    static void move();
    static void draw();
    static void takeDamage(int dmg);
    float hitPoints, exp;
    int playerId;

private:

    Player();

    ~Player(Player&);

};
