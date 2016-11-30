#ifndef _MonsterSpriteLayer_H_
#define _MonsterSpriteLayer_H_


#include"cocos2d.h"
#include"Observer.h"
using namespace cocos2d;

class MonsterSpriteLayer :public Layer{
public:
	bool init();
	/*怪物被射中减少怪物个数*/
	void monsterNumberDecrease();
	/*根据瓦片地图的信息设置怪物位置*/
	void setMonstersPosition(TMXObjectGroup* monsterObjectGroup);
	/*获得怪物剩余个数*/
	int getMonsterNumber();

	void onContact();

	void addObserver(Observer* observer);

	void update(float dt);
	CREATE_FUNC(MonsterSpriteLayer);
public:
	static int step;
private:

	Observer* _observer;

	int monsterNumber = 4;
	char name[20];
	LabelTTF* labelMonsterNumLeft;
	/*存放怪物精灵的容器*/
	Vector<Sprite*>vecMonsterSprite;

};

#endif