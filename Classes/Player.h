#ifndef __Player_H__
#define __Player_H__
#include "cocos2d.h"
USING_NS_CC;

class Player : public cocos2d::CCLayer {
public:
	virtual bool init();
	virtual void onEnter();

	void ccTouchesBegan(CCSet* touches, CCEvent* event);
	void ccTouchesEnded(CCSet* touches, CCEvent* event);
	bool isTouchInside(CCSprite* sprite, CCTouch* touch);
	void StartMoving(float f);

	CCSprite* getPlayerSprite() { return playerSprite; }
	bool getIsLeftPressed() { return isLeftPressed; }
	bool getIsRightPressed() { return isRightPressed; }
	void setPlayerSprite(char* name) { playerSprite = CCSprite::create(name); }
	void setIsLeftPressed(bool value) { isLeftPressed = value; }
	void setIsRightPressed(bool value) { isRightPressed = value; }

private:
	bool isLeftPressed;
	bool isRightPressed;
	CCSprite* playerSprite;
};


#endif