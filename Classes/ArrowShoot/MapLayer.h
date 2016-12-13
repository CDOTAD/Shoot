#ifndef _MapScene_H_
#define _MapScene_H_
#include"cocos2d.h"
using namespace cocos2d;

class MapLayer :public Layer{
public:

	virtual bool init();
	/*������Ƭ��ͼ*/
	TMXTiledMap* getMap();
	CREATE_FUNC(MapLayer);
public:
	static int step;
public:
	/*������Ƭ��ͼ�еĶ����*/
	TMXObjectGroup* getObjectGroup();
private:
	TMXObjectGroup* objGroup;
	TMXTiledMap* map;
};



#endif