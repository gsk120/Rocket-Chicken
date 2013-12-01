#ifndef __PLAYER_LAYER_H__
#define __PLAYER_LAYER_H__
#include "cocos2d.h"
#include "Player.h"
USING_NS_CC;

class PlayerLayer : public cocos2d::CCLayer {
public:
	virtual bool init();
	virtual void onEnter();

	void ccTouchesBegan(CCSet* touches, CCEvent* event);
	void ccTouchesEnded(CCSet* touches, CCEvent* event);
	bool isTouchInside(CCSprite* sprite, CCTouch* touch);
	void StartMoving(float f);
	void AnimationStart();

	Player* getPlayerSprite() { return playerSprite; }
	bool getIsLeftPressed() { return isLeftPressed; }
	bool getIsRightPressed() { return isRightPressed; }
	void setPlayerSprite(char* name) { playerSprite = Player::create(name); }
	void setIsLeftPressed(bool value) { isLeftPressed = value; }
	void setIsRightPressed(bool value) { isRightPressed = value; }

private:
	bool isLeftPressed;
	bool isRightPressed;
	Player* playerSprite;
};


#endif