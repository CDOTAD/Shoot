#pragma once
#include"cocos2d.h"
#include"Observer.h"
#include"ArrowSpriteLayer.h"
#include"MonsterSpriteLayer.h"
#include"MapLayer.h"
#include"PauseLayer.h"




using namespace cocos2d;




class GameLayer:public Layer ,public Observer,public PauseObserver
{
public:

	virtual bool init() = 0;
	virtual void update(float dt) = 0;
	virtual void setBurning(float dt)=0;
	virtual void onEventHappen(Layer* object, MyEvent e) = 0;
	virtual void onAgain(Layer* objcet) = 0;
	virtual void onResume(Layer* objcet);
	
public:
	void deleteBurning(float dt);
	void menuExitCallBack(cocos2d::Ref* pSender);
	
	bool isPause();
protected:

	void setMap(MapLayer* mapLayer);

	void setCommonPart();

	void setArrowLayer(ArrowSpriteLayer* arrowLayer);

	void setMonsterLayer(MonsterSpriteLayer* monsterLayer);

	void setHero(Sprite* myHero);

	void setListener();

	void Pause();

protected:
	bool _flagBurning = false;

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

private:
	PauseLayer* _pauseLayer;

	bool _flagPressed = false;
	Vec2 _speed;


};