

#include "Player.h"

Player::Player()
{
    hitPoints = exp = 0;
	vel = new Vector();
}

void Player::spawn()
{	
}

void Player::takeDamage(int dmg)
{
}

void Player::move()
{


}

void Player::draw()
{


}

void Player::update()
{

}


Player::~Player()
{
	delete vel;
	vel = nullptr;

    hitPoints = exp = 0;
}