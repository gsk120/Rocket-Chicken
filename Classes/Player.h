#ifndef __PLAYER_H__
#define _PLAYER_H__
#include "cocos2d.h"

USING_NS_CC;

class Player : public CCSprite
{
public:
	Player();
	~Player();

	static Player* create(const char* player);
};

#endif