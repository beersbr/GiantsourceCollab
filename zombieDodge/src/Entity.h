#ifndef __ENTITY_H__
#define __ENTITY_H__
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include "Vector.h"
#include "Size.h"

class Entity {
public:
    Entity();
    Entity(int x, int y, int z);
	virtual ~Entity();

    virtual void Draw(SDL_Renderer *renderer, SDL_Rect *camera) = 0;
	virtual void Update() = 0;


	int GetId();

public:
	Vector* pos;
    Vector* vel;
    SDL_Rect cameraOffset;
    SDL_Rect hitBox;

private:
	int _id;

	static int _ids;
	static int SetId();
};



/*
 Player* p = new Player();
 Monster* r = new Monster();                             d
 
 Entity* e = (Entity*)r;
 
 e->Draw();
 */


/*
 
 
 zGame->Run();
 
 Update(std::vector<Entity*> list)
 {
 
 for(int i=0; i < list.length; ++i;)
 
 {
 list[i]->Draw();
 }
 
 
 
 
 
 
 
 Vector a = Vector(1,1,1), b = Vector(2,2,2);
 
 Vector c = a+b;
 
 a+3;
 */

#endif