#ifndef _MainStep3Scene_H_
#define _MainStep3Scene_H_

#include"cocos2d.h"
#include<windows.h>
#include"ArrowSpriteLayer.h"
#include"MonsterSpriteLayer.h"
#include"MapLayer.h"
#include"PauseLayer.h"
#include"WinLayer.h"
#include"FailLayer.h"
#include"GameLayer.h"
#include"Observer.h"

using namespace cocos2d;


class PauseLayer;
class FailLayer;



class MainStep3Scene :public GameLayer{
public:
	static Scene* CreateScene();
	virtual bool init();
	virtual void update(float dt);
	virtual void setBurning(float dt);
	virtual void onEventHappen(Layer* object, MyEvent e);
public:
	void judge(float dt);
	void Pause();
	
	void deleteBurning(float dt);
	void menuExitCallBack(cocos2d::Ref* pSender);
	CREATE_FUNC(MainStep3Scene);
public:
	/*bool flagPressed = false;
	bool flagBurning = false;*/
	float scores = 0;
	static float Scores;
public:
	//ArrowSpriteLayer * arrow;//¼ýÍ·¾«Áé²ã
	//MonsterSpriteLayer* monster;//¹ÖÎï¾«Áé²ã
	//MapLayer* map;//ÍßÆ¬µØÍ¼²ã
private:
	int arrowleft = 0;

	Sprite* musicon;
	Sprite* myHero;
	Sprite* arch;
	PauseLayer* pauselayer;
	WinLayer* winlayer;
	FailLayer* faillayer;
	ParticleBatchNode* burningbatch;

	Vec2 speed;
	friend class ArrowSpriteLayer;
public:
	Vec2 getSpeed();
};
















#endif