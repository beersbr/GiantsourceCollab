//
// Created by Matt Jacobs on 1/9/14.
// Copyright (c) 2014 Brett Beers. All rights reserved.
//

#ifndef __ENEMY_H_
#define __ENEMY_H_
#include "Entity.h"
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>


class Enemy : public Entity{

public:
    Enemy();
    Enemy(int _x, int _y, int _z, std::string _playerTarget, int _hp);
	~Enemy();


    bool Spawn();
    //void Move();
    void Update(); // because it has to be there
    void Draw(SDL_Renderer *renderer);
    void TakeDamage(int dmg);


public:
	Vector* vel;
	Size<int> size;

	SDL_Texture* image;

    float hitPoints;
    float exp;
    std::string enemyId;
    bool isFollow = false;
    int moveSpeed = 10;
  

};

#endif // __ENEMY_H_