#include"Factory.h"
#include"MonsterSpriteStep1Layer.h"
#include"MonsterSpriteStep2Layer.h"
#include"MonsterSpriteStep3Layer.h"
#include"ArrowSpriteStep1Layer.h"
#include"ArrowSpriteStep2Layer.h"
#include"ArrowSpriteStep3Layer.h"
#include"MainScene.h"
#include"MainStep2Scene.h"
#include"MainStep3Scene.h"
//#include"MapStep1Layer.h"
//#include"MapStep2Layer.h"
//#include"MapStep3Layer.h"
Factory::Factory()
{
}

Factory::~Factory()
{
}


MonsterSpriteLayer* Factory::createMonsterSpriteLayer(MonsterStep monster) {
	switch (monster) {
	case MonsterSpriteStep1: {
		return MonsterSpriteStep1Layer::create();
	}
	case MonsterSpriteStep2: {
		return MonsterSpriteStep2Layer::create();
	}
	case MonsterSpriteStep3: {
		return MonsterSpriteStep3Layer::create();
	}
	}
}

ArrowSpriteLayer * Factory::createArrowSpriteLayer(ArrowStep arrow)
{
	switch (arrow) {
	case ArrowSpriteStep1:{
			return ArrowSpriteStep1Layer::create();
		}
	case ArrowSpriteStep2:{
		return ArrowSpriteStep2Layer::create();
		}
	case ArrowSpriteStep3: {
		return ArrowSpriteStep3Layer::create();
	}
	}
}
//
//MapLayer * Factory::createMapLayer(MapStep map)
//{
//	switch (map) {
//	case MapStep1: {
//		return MapStep1Layer::create();
//	}
//	case MapStep2: {
//		return MapStep2Layer::create();
//	}
//	case MapStep3: {
//		return MapStep3Layer::create();
//	}
//	}
//}

Scene * Factory::createMainScene(MainStep mainstep)
{
	switch (mainstep) 
	{
		case MainStep1: {
			return MainScene::CreateScene();
		}
		case MainStep2: {
			return MainStep2Scene::CreateScene();
		}
		case MainStep3: {
			return MainStep3Scene::CreateScene();
		}
	}
}
