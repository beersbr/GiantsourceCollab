//
// Created by Matt Jacobs on 1/9/14.
// Copyright (c) 2014 Brett Beers. All rights reserved.
//

#ifndef __BULLET_H_
#define __BULLET_H_
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <SDL2_mixer/SDL_mixer.h>
#include "Entity.h"
#include "Vector.h"
#include "Sprite.h"
#include "jsonator.h"

class Bullet : public Entity {
public:
    Bullet(Vector* origin, Vector *_target,float _x, float _y, float _z,std::string owner, std::string type);
    ~Bullet();


    bool Spawn(Vector &v);
    //void Move();
    void Update(); // because it has to be there
    void Draw(SDL_Renderer *renderer, SDL_Rect *camera);
    SDL_Rect GetHitBox();
    SDL_Rect hitBox;
    Mix_Chunk *spawnFX = NULL;
    Vector* vel;
    int moveSpeed = 50;
    SDL_Texture* image;
    Sprite* sprite;
    Vector* target = nullptr;

    bool spawned = false;
    std::string bulletId;

    /***** SPRITE STUFF */
    float originX;
    int animationDelay;
    float originY;
    bool deleteBullet = false;
    int currentRow;
    int imgWidth;
    int imgHeight;
    int currentFrame;
    int frameEnd;
    int frameBegin;
    int frameX;
    int frameY;
    cJSON *bulletConfig = nullptr;
    std::string ownerId;
    std::string ownerType;
    SDL_Rect clip;


};

#endif // _BULLET_H_