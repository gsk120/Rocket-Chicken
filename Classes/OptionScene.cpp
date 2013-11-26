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

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object

	this->setTouchEnabled(true);

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

	right = CCSprite::create("right.png");
	left = CCSprite::create("left.png");
	chicken = CCSprite::create("chicken.png");
	left->setPosition(ccp(origin.x + (left->getContentSize().width*2)/3, origin.y + left->getContentSize().height ));
	right->setPosition(ccp(visibleSize.width - (right->getContentSize().width*2)/3, origin.y + right->getContentSize().height ));
	chicken->setPosition(ccp(visibleSize.width/2, origin.y + chicken->getContentSize().height));
	this->addChild(left, 1);
	this->addChild(right, 1);
	this->addChild(chicken, 1);


    
    return true;
}

void OptionSetting::ccTouchesBegan(CCSet *touches, CCEvent* event)	//터치가 시작하는 것을 인식하는 함수
{
	CCSetIterator it=touches->begin();
	CCTouch* touch=(CCTouch*)(*it);
	this->isRightPressed = false;
	this->isLeftPressed = false;

	if(this->isTouchInside(this->left, touch)) {
		this->isLeftPressed = true;
	}
	if(this->isTouchInside(this->right, touch)) {
		this->isRightPressed = true;
	}
	
	if(isLeftPressed == true || isRightPressed == true) {
		if(isLeftPressed == true && isRightPressed == true)
			return;
		this->schedule(schedule_selector(OptionSetting::StartMoving));
	}
}

void OptionSetting::ccTouchesEnded(CCSet *touches, CCEvent* event)		//터치가 끝나는것을 인식하는 함수
{
	CCSetIterator it=touches->begin();
	CCTouch* touch=(CCTouch*)(*it);

	if(isLeftPressed == true || isRightPressed == true) {
		this->unschedule(schedule_selector(OptionSetting::StartMoving));
	}
}

bool OptionSetting::isTouchInside(CCSprite* sprite, CCTouch* touch) {	//터치가 스프라이트 내부인지 검사하는 함수
	CCPoint touchPoint = touch->getLocation();
	CCRect rect = sprite->boundingBox();
	if(rect.containsPoint(touchPoint)) {
		return true;
	}
	return false;
}

void OptionSetting::StartMoving(float f) {
	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
	CCPoint chickenPoint = this->chicken->getPosition();
	CCPoint NewPoint;
	CCPoint moveStep = ccp(5,0);

	if(this->isRightPressed == true && chickenPoint.x <= visibleSize.width - this->chicken->getContentSize().width/2) {
		NewPoint = ccp(chickenPoint.x + moveStep.x , chickenPoint.y);
		this->chicken->setPosition(NewPoint);
	}
	else if(this->isLeftPressed == true && chickenPoint.x >= origin.x + this->chicken->getContentSize().width/2) {
		NewPoint = ccp(chickenPoint.x - moveStep.x , chickenPoint.y);
		this->chicken->setPosition(NewPoint);
	}
}

void OptionSetting::onEnter() {
	CCLayer::onEnter();
	this->init();
}

void OptionScene::runThisTest()
{
    CCLayer* pLayer = new OptionSetting();
    addChild(pLayer);
    pLayer->release();

    CCDirector::sharedDirector()->pushScene(this);
}