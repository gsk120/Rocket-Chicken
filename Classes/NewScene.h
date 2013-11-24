#ifndef __NEW_SCENE_H__
#define __NEW_SCENE_H__

#include "cocos2d.h"

USING_NS_CC;
using namespace std;

class NewScene : public CCScene	///상속가능한 새로운씬
{
public: 
    NewScene(bool bPortrait = false);
    virtual void onEnter();

    virtual void runThisTest() = 0;

    // The CallBack for back to the main menu scene
    virtual void MainMenuCallback(CCObject* pSender);
};

#endif