#pragma once
#ifndef _MONSTERPRODUCT_H_
#define _FACTORY_H_


#include <stdio.h>
#include"Observer.h"
#include"cocos2d.h"

class MonsterProduct :public Layer {
public:
	MonsterProduct();
	virtual ~MonsterProduct();
	virtual bool init() = 0;
	/*���ﱻ���м��ٹ������*/
	void monsterNumberDecrease();
	/*������Ƭ��ͼ����Ϣ���ù���λ��*/
	void setMonstersPosition(TMXObjectGroup* monsterObjectGroup);
	/*��ù���ʣ�����*/
	int getMonsterNumber();

	void onContact();

	void addObserver(Observer* observer);
	virtual MonsterProduct* operationMonster() = 0;
	void update(float dt);
	float timerand(int i);
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

class Monster1 :public MonsterProduct {
public:
	Monster1();
	virtual ~Monster1();
	MonsterProduct* operationMonster();
public:
	virtual bool init();

	CREATE_FUNC(Monster1);

};

class Monster2 :public MonsterProduct {

public:
	Monster2();
	~Monster2();
	MonsterProduct* operationMonster();
public:
	virtual bool init();

	CREATE_FUNC(Monster2);
};

class Monster3 :public MonsterProduct {

public:
	Monster3();
	~Monster3();
	MonsterProduct* operationMonster();
public:
	virtual bool init();

	CREATE_FUNC(Monster3);
};
#endif