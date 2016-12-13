#pragma once
#ifndef _SCENCEPRODUCT_H_
#define _SCENCEPRODUCT_H_


#include <stdio.h>
#include"Observer.h"
#include"cocos2d.h"
#include<windows.h>
#include"GameLayer.h"
#include"FailLayer.h"
#include"WinLayer.h"

#define TILE_SIZE 32
#define MAX_SCORES 100

using namespace cocos2d;

class FailLayer;
class WinLayer;

class SceneProduct :public GameLayer {
public:
	Scene* operationScene();
	static  Scene* CreateScene();
	virtual bool init();
	void update(float dt);
	void setBurning(float dt);
	void onEventHappen(Layer* object, MyEvent e);
	void onAgain(Layer* objcet);
	void onResume(Layer* objcet);
	void menuStartCallback(cocos2d::Ref* pSender);
	void menuCloseCallback(cocos2d::Ref* pSender);

	Vec2 getSpeed();
	CREATE_FUNC(SceneProduct);
};

class Scene1 :public SceneProduct {
public:
	static Scene* CreateScene();
	bool init();
	void update(float dt);
	void setBurning(float dt);
	void onEventHappen(Layer* object, MyEvent e);
	void Pause();
	void judge(float dt);
	void onAgain(Layer* objcet);
	Scene * operationScene();

public:
	void deleteBurning(float dt);
	void menuExitCallBack(cocos2d::Ref* pSender);
	CREATE_FUNC(Scene1);
public:
	float scores = 0;

private:
	int arrowleft = 0;

	Scene* _scene;

	Sprite* musicon;
	PauseLayer* pauselayer;
	WinLayer* winlayer;
	FailLayer* faillayer;
	ParticleBatchNode* burningbatch;

	Vec2 speed;
	friend class ArrowProduct;


};

class Scene2 :public SceneProduct {
public:
	static Scene* CreateScene();
	virtual bool init();

	virtual void setBurning(float dt) {};

	virtual void onEventHappen(Layer* object, MyEvent e);
	virtual void onAgain(Layer* objcet);

	virtual void update(float dt);
	void menuExitCallBack(cocos2d::Ref* pSender);
	void Pause();
	Scene* operationScene();
	void judge(float dt);
	CREATE_FUNC(Scene2);
public:
	/*bool flagPressed = false;*/
	static float Scores;
	float scores = 0;
public:
	//ArrowSpriteLayer* arrow;//¼ýÍ·¾«Áé²ã
	//MonsterSpriteLayer* monster;//¹ÖÎï¾«Áé²ã
	//MapLayer* map;//ÍßÆ¬µØÍ¼²ã
private:
	int arrowleft = 0;

	Sprite* musicon;
	//Sprite* myHero;
	//Sprite* arch;
	PauseLayer* pauselayer;
	WinLayer* winlayer;
	FailLayer* faillayer;
	ParticleBatchNode* burningbatch;

	Vec2 speed;
	friend class ArrowProduct;
};

class Scene3 :public SceneProduct {

public:
	static Scene* CreateScene();
	virtual bool init();
	virtual void update(float dt);
	void Pause();
	virtual void setBurning(float dt);
	virtual void onEventHappen(Layer* object, MyEvent e);
	virtual void onAgain(Layer* objcet);
public:
	Scene* operationScene();

	void deleteBurning(float dt);
	void menuExitCallBack(cocos2d::Ref* pSender);
	CREATE_FUNC(Scene3);
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
	//Sprite* myHero;
	//Sprite* arch;
	PauseLayer* pauselayer;
	WinLayer* winlayer;
	FailLayer* faillayer;
	ParticleBatchNode* burningbatch;

	Vec2 speed;
	friend class ArrowProduct;
};

#endif