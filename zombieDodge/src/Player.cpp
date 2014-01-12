#include "Player.h"

Player::Player()
{
    hitPoints = exp = 0;
	vel = new Vector();

	SDL_Surface* tempSurface = IMG_Load("player.png");

	if(tempSurface == NULL)
		return;

	image = SDL_ConvertSurface(tempSurface, tempSurface->format, NULL);

	if(image == NULL)
	{
		SDL_FreeSurface(tempSurface);
		return;
	}

	SDL_FreeSurface(tempSurface);
	tempSurface = NULL;
}

void Player::Spawn()
{

}

void Player::TakeDamage(int dmg)
{

}

void Player::Move()
{

}

void Player::Draw()
{

}

void Player::Update()
{

}

Player::~Player()
{
	delete vel;
	vel = nullptr;

    hitPoints = exp = 0;
}