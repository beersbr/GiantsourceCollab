
#include "Entity.h"

int Entity::_ids = 0;
int Entity::SetId()
{
	return (++_ids);
}


Entity::Entity()
{
	pos = new Vector();
	_id = Entity::SetId();
}

Entity::Entity(int x, int y, int z)
{
	pos = new Vector(x, y, z);
	_id = Entity::SetId();
}

Entity::~Entity()
{
	delete pos;
	pos = nullptr;
}

int Entity::GetId()
{
	return _id;
}

void Entity::Update() {



}

void Entity::Draw(SDL_Renderer *renderer) {



}
