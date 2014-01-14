#ifndef  ENEMY_H
#define ENEMY_H

#include "Entity.h"
#include "Vector.h"

class Enemy : public Entity {

public:


    Enemy() : Entity(){};
    Enemy(int _x=0, int _y=0, int _z=0) : Entity(_x,_y,_z){};

    Vector pos;

    float hitPoints, exp;
    int moveSpeed = 150; // pixels/second


    int configIndex;
    std::string name;

    virtual void Update();
    static void Spawn();
    static void Move();

    virtual  void TakeDamage(int dmg);

    virtual void Draw();

};


#endif