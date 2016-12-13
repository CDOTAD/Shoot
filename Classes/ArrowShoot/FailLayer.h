#ifndef _FailLayer_H_
#define _FailLayer_H_

#include "SceneProduct.h"
#include"cocos2d.h"
using namespace cocos2d;

class Scene1;
class Scene2;
class Scene3;

class FailLayer :public Layer{
public:
	static Scene* CreateScene();
	virtual bool init();
	void menuAgainCallBack(cocos2d::Ref* pSender);
	void menuMenuCallBack(cocos2d::Ref* pSender);
	void menuExitCallBack(cocos2d::Ref* pSender);
	CREATE_FUNC(FailLayer);
public:
	Scene1* mainPlayLayer = NULL;
	Scene2* mainStep2Layer = NULL;
	Scene3* mainStep3Layer = NULL;
private:
	Sprite* background;
};



#endif