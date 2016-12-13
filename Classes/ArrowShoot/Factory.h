#ifndef _FACTORY_H_
#define _FACTORY_H_

#include"cocos2d.h"
#include"MonsterSpriteLayer.h"
#include"ArrowSpriteLayer.h"
#include"MapLayer.h"
#include"MainScene.h"
using namespace cocos2d;

enum MonsterStep
	{
		MonsterSpriteStep1,
		MonsterSpriteStep2,
		MonsterSpriteStep3
	};
enum ArrowStep
{
	ArrowSpriteStep1,
	ArrowSpriteStep2,
	ArrowSpriteStep3
};
enum MapStep {
	MapStep1,
	MapStep2,
	MapStep3
};
enum MainStep {
	MainStep1,
	MainStep2,
	MainStep3
};


class Factory {
public :
	
	Factory();
	~Factory();

public :
	static MonsterSpriteLayer* createMonsterSpriteLayer(MonsterStep monster);
	static ArrowSpriteLayer* createArrowSpriteLayer(ArrowStep arrow);
	static MapLayer* createMapLayer(MapStep map);
	static Scene* createMainScene(MainStep mainstep);
};

#endif
