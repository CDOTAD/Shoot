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
	Sprite* getSprite();
	void setPosition(float x, float y);
	const Vec2& getPosition() const;


	
private:
	Sprite* _sprite;

};



#endif // !_HeroSprite_H_
