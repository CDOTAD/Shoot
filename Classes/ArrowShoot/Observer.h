#pragma once
#include"cocos2d.h"

#define MONSTER_LAYER_TAG 0
#define ARROW_LAYER_TAG 1

using namespace cocos2d;




enum MyEvent{NoArrow,NoMonster,ArrowRotate,Contact,ArrowOut};

class Observer
{
public:
	virtual void onEventHappen(Layer* object, MyEvent e) = 0;
};