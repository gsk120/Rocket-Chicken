#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "NewScene.h"
#include "PlayerLayer.h"
#include "Enemy.h"
#include <stdlib.h>

USING_NS_CC;

class GamePlay : public cocos2d::CCLayer
{
public:
	GamePlay();
	~GamePlay();
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
	virtual bool background();
	virtual void SpawnEnemy(float dt);
	virtual void onEnter();
	
	void update(float dt);
	void MoveBackground(float dt);
	void Done(CCNode* sender);
	void setPlayerLayer(PlayerLayer* pPlay) { pPlayerLayer = pPlay; }
	void CollisionDetecter(float dt);

private:
	CCSprite* m_pBackground1;
	CCSprite* m_pBackground2;
	PlayerLayer* pPlayerLayer;		//충돌검사를 위해 받아옴
protected:
	CCArray* enemyArray;		//적들을 배열에 저장 역시 충돌을 위해
};

class GameScene : public NewScene {
public:
    virtual void runThisTest();
};

#endif