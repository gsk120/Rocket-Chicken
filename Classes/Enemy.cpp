#include "Enemy.h"

Enemy::Enemy()
{
}

Enemy::~Enemy()
{
}

Enemy* Enemy::create(const char* enemyName, const CCRect& rect)
{
	Enemy* pSprite = new Enemy();

	
	if(pSprite && pSprite->initWithFile(enemyName, rect))
	{
		pSprite->autorelease();

		return pSprite;
	}

	CC_SAFE_DELETE(pSprite);

	return NULL;
}
