#ifndef _ArrowSprite_H_
#define _ArrowSprite_H_

#include"ArmSprite.h"

using namespace cocos2d;

class ArrowSprite :public ArmSprite 
{
public:
	ArrowSprite();
	~ArrowSprite();

public:
	bool isFly();
	void setPhysicsBody();
	Action* runAction(Action* action);
	void onContact();
	Vec2 getSpeed();
	PhysicsBody* getPhysicsBody();

private:
	bool _isFly;
	Vec2 _speed;

};



#endif // !_ArrowSprite_H_
