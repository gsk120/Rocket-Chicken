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

    /////////////////////////////
    // 3. add your codes below...

	CCLabelTTF* pLabel = CCLabelTTF::create("Game Scene", "Arial", 24);
    
    // position the label on the center of the screen
    pLabel->setPosition(ccp(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - pLabel->getContentSize().height));

    // add the label as a child to this layer
    this->addChild(pLabel, 1);
    
    return true;
}

bool GamePlay::background()
{
	m_pBackground1 = CCSprite::create("Background.png");
	m_pBackground1->setPosition(CCPointZero);
	m_pBackground1->setAnchorPoint(ccp(0.0f, 0.0f));
	addChild(m_pBackground1, 0);

	m_pBackground2 = CCSprite::create("Background.png");
	m_pBackground2->setPosition(ccp(0.0f, 800.0f));
	m_pBackground2->setAnchorPoint(ccp(0.0f, 0.0f));
	addChild(m_pBackground2, 0);

	scheduleUpdate();

	return true;
}

void GamePlay::onEnter()		//Game Start에 레이어생성 : Layer의 온 엔터
{
    CCLayer::onEnter();
	this->background();
	this->init();
}

void GameScene::runThisTest()		//Game Start에 들어왔을때 레이어 생성하여 씬에 추가 및 씬 전환
{
	GamePlay* pLayer = new GamePlay();
    addChild(pLayer);
	PlayerLayer* pPlayer = new PlayerLayer();
	addChild(pPlayer);
    pLayer->release();
	pPlayer->release();

	CCDirector::sharedDirector()->pushScene(this);
}

void GamePlay::update(float dt)
{
	MoveBackground(dt);
}

void GamePlay::MoveBackground(float dt)
{
	float deltaY = 200.f * dt;
	CCPoint moveStep = ccp(0.0f, -deltaY);

	m_pBackground1->setPosition(ccpAdd(m_pBackground1->getPosition(), moveStep));
	m_pBackground2->setPosition(ccpAdd(m_pBackground2->getPosition(), moveStep));

	float contentHeight = m_pBackground1->getContentSize().height;

	if(m_pBackground1->getPosition().y <= -contentHeight)
	{
		CCPoint newPos = m_pBackground1->getPosition();
		newPos.y = m_pBackground2->getPosition().y + contentHeight;
		m_pBackground1->setPosition(newPos);
	}

	else if(m_pBackground2->getPosition().y <= -contentHeight)
	{
		CCPoint newPos = m_pBackground2->getPosition();
		newPos.y = m_pBackground1->getPosition().y + contentHeight;
		m_pBackground2->setPosition(newPos);
	}
}