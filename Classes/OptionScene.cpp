#include "OptionScene.h"

bool OptionSetting::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

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

    /////////////////////////////
    // 3. add your codes below...

	CCLabelTTF* pLabel = CCLabelTTF::create("Option Scene", "Arial", 24);
    
    // position the label on the center of the screen
    pLabel->setPosition(ccp(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - pLabel->getContentSize().height));

    // add the label as a child to this layer
    this->addChild(pLabel, 1);
   
    return true;
}

void OptionSetting::onEnter() {
	CCLayer::onEnter();
	this->init();
}

void OptionScene::runThisTest()
{
    CCLayer* pLayer = new OptionSetting();
	CCLayer* pPlayerLayer = new PlayerLayer();
    addChild(pLayer);
	addChild(pPlayerLayer);
    pLayer->release();
	pPlayerLayer->release();

    CCDirector::sharedDirector()->pushScene(this);
}