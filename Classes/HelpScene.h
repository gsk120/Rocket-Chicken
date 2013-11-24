#ifndef __HELP_SCENE_H__
#define __HELP_SCENE_H__

#include "NewScene.h"
USING_NS_CC;

class HelpView : public cocos2d::CCLayer
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
	void menuCloseCallback(CCObject* pSender);

};

class HelpScene : public NewScene {
public:
    virtual void runThisTest();
};

#endif