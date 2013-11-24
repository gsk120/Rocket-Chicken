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
        //pScene = new ActionsTestScene();
		break;
    case MENU_OPTION:
       // pScene = new TransitionsTestScene();
		break;
	case MENU_HELP:
		//pScene = new HelpScene();
		break;
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
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
                                        "CloseNormal.png",
                                        "CloseSelected.png",
                                        this,
                                        menu_selector(MainScene::menuCloseCallback));
    
	pCloseItem->setPosition(ccp(origin.x + visibleSize.width - pCloseItem->getContentSize().width/2 ,
                                origin.y + pCloseItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    CCMenu* pMenu = CCMenu::create(pCloseItem, NULL);
    pMenu->setPosition(CCPointZero);
    this->addChild(pMenu, 1);

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

	// add the label as a child to this layer

    // add "Main" splash screen"
    //CCSprite* pSprite = CCSprite::create("HelloWorld.png");

    // position the sprite on the center of the screen
    //pSprite->setPosition(ccp(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

    // add the sprite as a child to this layer
   // this->addChild(pSprite, 0);
    
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