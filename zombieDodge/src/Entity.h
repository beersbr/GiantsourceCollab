class Entity {
public:
    Entity() {x=y=z=0;}
    Entity(int _x, int _y, int _z) {x=_x; y=_y; z=_z;}
    int x,y,z;



    virtual void Draw() = 0;

private:

    float secret;


};

class Player : public Entity {

public:

    Player() : Entity(){};
    Player(int _x=0, int _y=0, int _z=0) : Entity(_x,_y,_z){};

    Vector pos;

    virtual void Draw() {

        Entity::Draw();

    }

};


class Monster : public Entity {

public:

    Monster() : Entity(){};
    Monster(int _x=0, int _y=0, int _z=0) : Entity(_x,_y,_z){};

    virtual void Draw() {



    };

};

/*
              Player* p = new Player();
              Monster* r = new Monster();

              Entity* e = (Entity*)r;

              e->Draw();
               */


/*

zombieGame* zGame = zombieGame::getInstance();
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