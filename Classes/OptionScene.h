#ifndef __OPTION_SCENE_H__
#define __OPTION_SCENE_H__

#include "NewScene.h"
USING_NS_CC;

class OptionSetting : public cocos2d::CCLayer
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
	virtual void onEnter();

	void ccTouchesBegan(CCSet* touches, CCEvent* event);
	void ccTouchesEnded(CCSet* touches, CCEvent* event);
	bool isTouchInside(CCSprite* sprite, CCTouch* touch);
	void StartMoving(float f);

	CCSprite* left;
	bool isLeftPressed;
	CCSprite* right;
	bool isRightPressed;
	CCSprite* chicken;

};

class OptionScene : public NewScene {
public:
    virtual void runThisTest();
};

#endif