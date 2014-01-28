//
// Created by Matt Jacobs on 1/9/14.
// Copyright (c) 2014 Brett Beers. All rights reserved.
//

#ifndef __ENEMY_H_
#define __ENEMY_H_
#include <stdio.h>
#include "Entity.h"
#include "Sprite.h"
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <SDL2_mixer/SDL_mixer.h>

class Enemy : public Entity{

public:
    Enemy();
    Enemy(int _x, int _y, int _z, std::string _playerTarget, int _hp);
	~Enemy();


    bool Spawn();
    //void Move();
    void Update(); // because it has to be there
    void Draw(SDL_Renderer *renderer,SDL_Rect *camera);
    void TakeDamage(int dmg);
    SDL_Rect GetHitBox();

public:
	Vector* vel;
	Size<int> size;
    SDL_Rect hitBox;
	//SDL_Texture* image;
    Sprite* sprite;
    Mix_Chunk *spawnFX = NULL;

    float hitPoints;
    float exp;
    std::string enemyId;
    bool isFollow = false;
    int moveSpeed = 10;

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
    bool deleteItem = false;
    SDL_Rect clip;
  

};

#endif // __ENEMY_H_