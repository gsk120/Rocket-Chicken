#ifndef _ENEMY_
#define _ENEMY_

#include "cocos2d.h"

USING_NS_CC;

class Enemy : public CCSprite
{
public:
	Enemy();
	~Enemy();

	static Enemy* create(const char* enemyName, const CCRect& rect);


};

#endif