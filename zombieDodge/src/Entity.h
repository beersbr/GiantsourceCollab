#ifndef  ENTITY_H
#define ENTITY_H

class Entity {
public:
    Entity() {x=y=z=0;}
    Entity(int _x, int _y, int _z) {x=_x; y=_y; z=_z;}
    int x,y,z;

    virtual void Draw() = 0;

private:

    float secret;


};






/*
              Player* p = new Player();
              Monster* r = new Monster();

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