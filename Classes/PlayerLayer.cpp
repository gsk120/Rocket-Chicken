#include "PlayerLayer.h"

bool PlayerLayer::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
	
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

	this->setTouchEnabled(true);		//��ġ �ν� ����
   
	this->setPlayerSprite("chicken.png");		//�÷��̾� ĳ���� ����
	this->playerSprite->setPosition(ccp(visibleSize.width/2, origin.y + this->playerSprite->getContentSize().height));
	this->addChild(this->playerSprite, 1);
   
    return true;
}

void PlayerLayer::ccTouchesBegan(CCSet *touches, CCEvent* event)	//��ġ�� �����ϴ� ���� �ν��ϴ� �Լ�
{
	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	CCSetIterator it=touches->begin();
	CCTouch* touch=(CCTouch*)(*it);
	CCPoint touchPoint = touch->getLocation();
	this->setIsRightPressed(false);
	this->setIsLeftPressed(false);

	if(touchPoint.x <= visibleSize.width/2) {
		this->setIsLeftPressed(true);
	}
	if(touchPoint.x > visibleSize.width/2) {
		this->setIsRightPressed(true);
	}
	
	if(this->isLeftPressed == true || this->isRightPressed == true) {
		if(this->isLeftPressed == true && this->isRightPressed == true)
			return;
		this->schedule(schedule_selector(PlayerLayer::StartMoving));
	}
}

void PlayerLayer::ccTouchesEnded(CCSet *touches, CCEvent* event)		//��ġ�� �����°��� �ν��ϴ� �Լ�
{
	CCSetIterator it=touches->begin();
	CCTouch* touch=(CCTouch*)(*it);

	if(this->isLeftPressed == true || this->isRightPressed == true) {
		this->unschedule(schedule_selector(PlayerLayer::StartMoving));
	}
}

bool PlayerLayer::isTouchInside(CCSprite* sprite, CCTouch* touch) {	//��ġ�� ��������Ʈ �������� �˻��ϴ� �Լ�
	CCPoint touchPoint = touch->getLocation();					//����� �������� ���߿� ������ ������ ����
	CCRect rect = sprite->boundingBox();
	if(rect.containsPoint(touchPoint)) {
		return true;
	}
	return false;
}

void PlayerLayer::StartMoving(float f) {
	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
	CCPoint chickenPoint = this->playerSprite->getPosition();
	CCPoint NewPoint;
	CCPoint moveStep = ccp(5,0);

	if(this->isRightPressed == true && chickenPoint.x <= visibleSize.width - this->playerSprite->getContentSize().width/2) {
		NewPoint = ccp(chickenPoint.x + moveStep.x , chickenPoint.y);
		this->playerSprite->setPosition(NewPoint);
	}
	else if(this->isLeftPressed == true && chickenPoint.x >= origin.x + this->playerSprite->getContentSize().width/2) {
		NewPoint = ccp(chickenPoint.x - moveStep.x , chickenPoint.y);
		this->playerSprite->setPosition(NewPoint);
	}
}

void PlayerLayer::onEnter() {
	CCLayer::onEnter();
	this->init();
}