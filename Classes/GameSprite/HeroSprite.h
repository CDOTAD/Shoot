#ifndef _HeroSprite_H_
#define _HeroSprite_H_

#include"cocos2d.h"

using namespace cocos2d;

class HeroSprite :public Node 
{
public:
	HeroSprite();
	~HeroSprite();

	
	void bingSprite(Sprite* sprite);

public:
	void setPosition(float x, float y);
	const Vec2& getPosition() const;
	PhysicsBody* getPhysicsBody();
	void setTag(int tag);
	void setVisible(bool visible);
	Size getContentSize();
	virtual void setPhysicsBody();

	



	
protected:
	Sprite* _sprite;
	PhysicsBody* _physicsBody;

};



#endif // !_HeroSprite_H_
