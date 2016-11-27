#ifndef _MonsterSpriteLayer_H_
#define _MonsterSpriteLayer_H_
#define MONSTERS_NUM 4

#include"cocos2d.h"
using namespace cocos2d;

class MonsterSpriteLayer :public Layer{
public:
	static MonsterSpriteLayer* createMonster();
	bool init();
	/*���ﱻ���м��ٹ������*/
	void monsterNumberDecrease();
	/*������Ƭ��ͼ����Ϣ���ù���λ��*/
	void setMonstersPosition(TMXObjectGroup* monsterObjectGroup);
	/*��ù���ʣ�����*/
	int getMonsterNumber();
	void update(float dt);
	CREATE_FUNC(MonsterSpriteLayer);
public:
	static int step;
private:
	int monsterNumber = 4;
	char name[20];
	LabelTTF* labelMonsterNumLeft;
	/*��Ź��ﾫ�������*/
	Vector<Sprite*>vecMonsterSprite;

};

#endif