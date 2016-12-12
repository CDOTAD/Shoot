#pragma once
#include"cocos2d.h"

#define MONSTER_LAYER_TAG 0
#define ARROW_LAYER_TAG 1

#define STEP_ONE_ARROW 10
#define STEP_TWO_ARROW 7
#define STEP_THREE_ARROW 6

#define MONSTER_NUM 4

using namespace cocos2d;




enum MyEvent{NoArrow,NoMonster,ArrowRotate,Contact,ArrowOut};

class Observer
{
public:
	virtual void onEventHappen(Layer* object, MyEvent e) = 0;
};

class PauseObserver
{
public:
	virtual void onResume(Layer* object) = 0;
	virtual void onAgain(Layer* objcet) = 0;
};