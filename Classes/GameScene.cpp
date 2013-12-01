#include "GameScene.h"

GamePlay::GamePlay() {
	enemyArray = nullptr;
}

GamePlay::~GamePlay() {
	if(enemyArray) {
		enemyArray->release();
		enemyArray = nullptr;
	}
}

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
    
	this->schedule(schedule_selector(GamePlay::CollisionDetecter));

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

void GamePlay::SpawnEnemy(float dt)
{
	int location, seed;

	srand(GetTickCount());

	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

	Enemy* pEnemy;
	CCMoveTo *pAction;
	CCFiniteTimeAction* actionDone = CCCallFuncN::create(this, callfuncN_selector(GamePlay::Done));

	seed = rand() % 2;

	switch(seed){
	
	case 0:
		pEnemy = Enemy::create("Airplain.png", CCRectMake(0.0f, 0.0f, 70, 38));
		location = (rand() % 6) + 4;
		pEnemy->setPosition(ccp(visibleSize.width, (visibleSize.height) * location / 9));
		location = (rand() % 2);
		pAction = CCMoveTo::create(5.0, ccp(0, (visibleSize.height) * location / 9));
		pEnemy->runAction( CCSequence::create(pAction, actionDone, nullptr));
		this->addChild(pEnemy);

		pEnemy->setTag(1);			//충돌 검사를 위해 태그 설정해서 적 배열에 저장
		enemyArray->addObject(pEnemy);

		break;
	
	case 1:
		pEnemy = Enemy::create("Airplain.png", CCRectMake(0.0f, 0.0f, 70, 38));
		pEnemy->setFlipX(true);
		location = (rand() % 6) + 4;
		pEnemy->setPosition(ccp(0, (visibleSize.height) * location / 9));
		location = (rand() % 2);
		pAction = CCMoveTo::create(5.0, ccp(visibleSize.width, (visibleSize.height) * location / 9));
		pEnemy->runAction( CCSequence::create(pAction, actionDone, nullptr));
		this->addChild(pEnemy);

		pEnemy->setTag(1);			//충돌 검사를 위해 태그 설정해서 적배열에 저장
		enemyArray->addObject(pEnemy);

		break;
	}



}

void GamePlay::Done(CCNode* sender)
{
	CCSprite *sprite = (CCSprite *) sender;
	this->removeChild(sprite, true);
}


void GamePlay::onEnter()		//Game Start에 레이어생성 : Layer의 온 엔터
{
    CCLayer::onEnter();
	this->background();
	this->init();
	enemyArray = new CCArray;
	this->schedule(schedule_selector(GamePlay::SpawnEnemy), 3);
}

void GameScene::runThisTest()		//Game Start에 들어왔을때 레이어 생성하여 씬에 추가 및 씬 전환
{
	GamePlay* pLayer = new GamePlay();
	PlayerLayer* pPlayer = new PlayerLayer();
	pLayer->setPlayerLayer(pPlayer);
    addChild(pLayer);
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

void GamePlay::CollisionDetecter(float dt) {
	CCArray* enemyToDelete = new CCArray;		//충돌하면 어케할지 미정이라 걍 적 삭제하는걸로 실험함
	
	CCObject* it = NULL;
	CCRect playerRect = CCRectMake(
		this->pPlayerLayer->getPlayerSprite()->getPosition().x - (this->pPlayerLayer->getPlayerSprite()->boundingBox().size.width/2),
		this->pPlayerLayer->getPlayerSprite()->getPosition().y - (this->pPlayerLayer->getPlayerSprite()->boundingBox().size.height/2),
		this->pPlayerLayer->getPlayerSprite()->boundingBox().size.width,
		this->pPlayerLayer->getPlayerSprite()->boundingBox().size.height);
	CCARRAY_FOREACH(enemyArray, it) {									// CCArray 전용 for문임 ㅇㅇ
		Enemy* pEnemy = static_cast<Enemy*>(it);
		CCRect enemyRect = CCRectMake(
			pEnemy->getPosition().x - (pEnemy->getContentSize().width/2),
			pEnemy->getPosition().y - (pEnemy->getContentSize().height/2),
			pEnemy->getContentSize().width,
			pEnemy->getContentSize().height);
		if(playerRect.intersectsRect(enemyRect)) {
			enemyToDelete->addObject(pEnemy);		//여기가 충돌 발생시 해야할 일 ///일단 여기서는 배열에 저장하여 삭제할것임
		}
	}
	CCARRAY_FOREACH(enemyToDelete, it) {
		Enemy* pEnemy = static_cast<Enemy*>(it);
		enemyArray->removeObject(pEnemy);
		this->removeChild(pEnemy, true);
	}
	enemyToDelete->release();
}

