#ifndef _PauseLayer_H_
#define _PauseLayer_H_

#include"cocos2d.h"
#include"Observer.h"
using namespace cocos2d;


class PauseLayer :public Layer{
public:
	static Scene* CreateScene();
	virtual bool init();
	void menuAgainCallBack(cocos2d::Ref* pSender);
	void menuResumeCallBack(cocos2d::Ref* pSender);
	void menuExitCallBack(cocos2d::Ref* pSender);

	void addObserver(PauseObserver* observer);

	CREATE_FUNC(PauseLayer);
public:
	static int step;
private:
	Sprite* background;

	PauseObserver* _observer;

public:
	
	

};


#endif