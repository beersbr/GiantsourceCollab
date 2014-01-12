#ifndef __ENTITY_H__
#define __ENTITY_H__

#include "Vector.h"

class Entity {
public:
    Entity();
    Entity(int x, int y, int z);
	virtual ~Entity();

    virtual void Draw() = 0;
	virtual void Update() = 0;

	int GetId();

public:
	Vector* pos;

private:
	int _id;

	static int _ids;
	static int SetId();
};

#endif