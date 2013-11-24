#include "NewScene.h"
#include "MainScene.h"

NewScene::NewScene(bool bPortrait)
{
    
    CCScene::init();
}

void NewScene::onEnter()
{
	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

    CCScene::onEnter();

    //add the menu item for back to main menu
//#if (CC_TARGET_PLATFORM == CC_PLATFORM_MARMALADE)
//    CCLabelBMFont* label = CCLabelBMFont::create("MainMenu",  "fonts/arial16.fnt");
//#else
    CCLabelTTF* label = CCLabelTTF::create("MainMenu", "Arial", 20);
//#endif
    CCMenuItemLabel* pMenuItem = CCMenuItemLabel::create(label, this, menu_selector(NewScene::MainMenuCallback));

    CCMenu* pMenu =CCMenu::create(pMenuItem, NULL);

    pMenu->setPosition( CCPointZero );
	pMenuItem->setPosition( ccp( visibleSize.width - 50, origin.y + 25) );

    addChild(pMenu, 1);
}

void NewScene::MainMenuCallback(CCObject* pSender)
{
    CCScene* pScene = CCScene::create();
    CCLayer* pLayer = new MainScene();
    pLayer->autorelease();

    pScene->addChild(pLayer);
    CCDirector::sharedDirector()->replaceScene(pScene);
}
