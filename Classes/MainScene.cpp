#include "MainScene.h"

#define LINE_SPACE 60
USING_NS_CC;

static NewScene* CreateTestScene(int nIdx)
{
    CCDirector::sharedDirector()->purgeCachedData();

    NewScene* pScene = NULL;

    switch (nIdx)
	{
    case MENU_START:
        pScene = new GameScene();
		break;
    case MENU_OPTION:
        pScene = new OptionScene();
		break;
	case MENU_HELP:
		pScene = new HelpScene();
		break;
	case MENU_EXIT:
		exit(0);
	default:
        break;
    }

    return pScene;
}


CCScene* MainScene::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    MainScene *layer = MainScene::create();

    // add layer as a child to scene
    scene->addChild(layer);
	
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool MainScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    
    // position the label on the center of the screen
	pGameMenu = CCMenu::create();
    for (int i = 0; i < COUNT; ++i)
    {

        CCLabelTTF* label = CCLabelTTF::create(g_aTestNames[i].c_str(), "Arial", 35); 
        CCMenuItemLabel* pMenuItem = CCMenuItemLabel::create(label, this, menu_selector(MainScene::menuCallback));
        pGameMenu->addChild(pMenuItem, i + 10000);
		pMenuItem->setPosition( ccp( visibleSize.width/2, ((visibleSize.height/2) - (i + 1) * LINE_SPACE) ));
    }
	
	pGameMenu->setContentSize(CCSizeMake(visibleSize.width, (COUNT + 1) * (LINE_SPACE)));
    pGameMenu->setPosition(CCPointZero);
    addChild(pGameMenu);
    
    return true;
}


void MainScene::menuCloseCallback(CCObject* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT) || (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
	CCMessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
#else
    CCDirector::sharedDirector()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
#endif
}

void MainScene::menuCallback(CCObject * pSender)
{
    // get the userdata, it's the index of the menu item clicked
    CCMenuItem* pMenuItem = (CCMenuItem *)(pSender);
    int nIdx = pMenuItem->getZOrder() - 10000;

    // create the test scene and run it
    NewScene* pScene = CreateTestScene(nIdx);
    if (pScene)
    {
        pScene->runThisTest();
        pScene->release();
    }
}