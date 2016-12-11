#ifndef _MonsterSpriteLayer_H_
#define _MonsterSpriteLayer_H_


#include"cocos2d.h"
#include"Observer.h"
using namespace cocos2d;

class MonsterSpriteLayer :public Layer{
public:
	virtual bool init() = 0;
	/*���ﱻ���м��ٹ������*/
	void monsterNumberDecrease();
	/*������Ƭ��ͼ����Ϣ���ù���λ��*/
	void setMonstersPosition(TMXObjectGroup* monsterObjectGroup);
	/*��ù���ʣ�����*/
	int getMonsterNumber();

	void onContact();

	void addObserver(Observer* observer);

	void update(float dt);
	float timerand(int i);
	//CREATE_FUNC(MonsterSpriteLayer);
//public:
//	static int step;
protected:
	void addMonster();


protected:

	Observer* _observer;

	int monsterNumber = 4;
	char name[20];
	LabelTTF* labelMonsterNumLeft;
	/*��Ź��ﾫ�������*/
	Vector<Sprite*>vecMonsterSprite;

};

#endif