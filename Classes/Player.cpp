#include "Player.h"

Player::Player()
{
}

Player::~Player()
{
}

Player* Player::create(const char* name) {
	Player* pSprite = new Player();
	pSprite->initWithFile(name);
	pSprite->setScale(0.2f);
	return pSprite;
}
