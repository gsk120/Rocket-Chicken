#include "GameScene.h"

bool GamePlay::init()
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
                                        menu_selector(NewScene::ReturnMainMenu));
    
	pCloseItem->setPosition(ccp(origin.x + visibleSize.width - pCloseItem->getContentSize().width/2 ,
                                origin.y + pCloseItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    CCMenu* pMenu = CCMenu::create(pCloseItem, NULL);
    pMenu->setPosition(CCPointZero);
    this->addChild(pMenu, 1);

	CCLabelTTF* pLabel = CCLabelTTF::create("Game Scene", "Arial", 24);
    
    // position the label on the center of the screen
    pLabel->setPosition(ccp(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - pLabel->getContentSize().height));

    // add the label as a child to this layer
    this->addChild(pLabel, 1);

    /////////////////////////////
    // 3. add your codes below...
    
    return true;
}

void GamePlay::onEnter()		//Game Start에 레이어생성 : Layer의 온 엔터
{
    CCLayer::onEnter();
	this->init();
}

void GameScene::runThisTest()		//Game Start에 들어왔을때 레이어 생성하여 씬에 추가 및 씬 전환
{
	GamePlay* pLayer = new GamePlay();
    addChild(pLayer);
    pLayer->release();

	CCDirector::sharedDirector()->pushScene(this);
}

