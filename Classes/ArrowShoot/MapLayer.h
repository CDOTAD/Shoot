#ifndef _MapScene_H_
#define _MapScene_H_
#include"cocos2d.h"
using namespace cocos2d;

class MapLayer :public Layer{
public:

	virtual bool init()=0;
	/*������Ƭ��ͼ*/
	TMXTiledMap* getMap();
	//CREATE_FUNC(MapLayer);
public:
	//static int step;
public:
	/*������Ƭ��ͼ�еĶ����*/
	TMXObjectGroup* getObjectGroup();
	void addMap(std::string file);
private:
	TMXObjectGroup* objGroup;
	TMXTiledMap* map;
};



#endif