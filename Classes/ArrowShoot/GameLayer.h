#pragma once
#include"cocos2d.h"
#include"ArrowSpriteLayer.h"
#include"MonsterSpriteLayer.h"
#include"MapLayer.h"
#include"Observer.h"



using namespace cocos2d;

class GameLayer:public Layer ,public Observer
{
public:
	
	virtual bool init() = 0;
	virtual void update(float dt) = 0;
	virtual void setBurning(float dt)=0;
	virtual void onEventHappen(Layer* object, MyEvent e) = 0;
public:
	void deleteBurning(float dt);
	void menuExitCallBack(cocos2d::Ref* pSender);
	
protected:
	bool _flagBurning = false;
	bool _flagPressed = false;

protected:
	ArrowSpriteLayer* _arrowLayer;
	MonsterSpriteLayer* _monsterLayer;
	MapLayer* _mapLayer;
	

	Sprite* _myHero;
	Sprite* _arch;
	EventListenerPhysicsContact* _contactListener;
	ParticleBatchNode* _burningBatch;

	
	
	int _arrowNumber;
	int _monsterNumber;



};