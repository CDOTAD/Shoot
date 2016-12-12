#ifndef _ArrowSpriteLayer_H_
#define _ArrowSpriteLayer_H_

#define ARROWS_NUM 10


#include"cocos2d.h"
#include"Observer.h"


using namespace cocos2d;

//class MainScene;
//class MainStep2Scene;
//class MainStep3Scene;

class ArrowSpriteLayer :public Layer
{
public:
	virtual bool init()=0;
	/*������������*/
	bool onTouchBegan(Touch* touch, Event* event);
	void onTouchEnded(Touch* touch, Event* event);
	void onTouchCancelled(Touch* touch, Event* event);
	void onMouseMove(Event* event);
	/*������Ƭ��ͼ�����Ϣ��ʼ������λ��*/
	void setArrowPosition(TMXObjectGroup* arrowObjectGroup);
	/*��ȡ��ͷ����*/
	Sprite* getArrowSprite();
	/*�ı��ͷ����ָ��ļ�ͷ*/
	void changeArrowSpriteReferTo();
	/*����ʱ��Ƶ��*/
	void setTimeFrequency();

	

	virtual void update(float dt);

	void updateLabel();

	void onContact();

	/*��ü�ͷ��ʣ�����*/
	int getArrowSpriteNumber();
	void addObserver(Observer* observer);
	//CREATE_FUNC(ArrowSpriteLayer);
protected:
	void setListener();

	void setLabel();

	void setArroSprite();
	
	


public:
	bool isflying = false;
	float scores = 0;

	
	/*MainScene* layer1;
	MainStep2Scene* layer2;
	MainStep3Scene* layer3;*/
protected:

	Observer* _observer;

	/*��ͷ����*/
	Sprite* _arrowSprite;

	int spriteNum;

	LabelTTF* labelArrowNumLeft;

	int ARROWNUMBER;

	//�洢ʱ��Ƶ��
	double timeFrequency;
	//�洢�����¼�����ʱ��ʱ��
	double touchBeganTime;
	//�洢�����¼�����ʱ��ʱ��
	double touchEndedTime;

	char name[20];
	/*���ڴ�ż�ͷ���������*/

	Vector<Sprite*> _vecArrowSprite;

	bool isPause = false;

	//Vector<Sprite*> vecArrowSprite;
};


#endif