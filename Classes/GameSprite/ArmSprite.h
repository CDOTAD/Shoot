#ifndef _ArmSprite_H_
#define _ArmSprite_H_

#include"HeroSprite.h"

using namespace cocos2d;

class ArmSprite :public HeroSprite 
{
public:
	ArmSprite();
	ArmSprite(Sprite* sprite);

	~ArmSprite();
public:
	void setRotation(float rotation);


};



#endif // !_ArmSprit_H_
