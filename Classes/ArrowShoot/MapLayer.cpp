#include"MapLayer.h"


TMXObjectGroup* MapLayer::getObjectGroup(){
	return this->objGroup;
}

void MapLayer::addMap(std::string file)
{
	auto str = String::createWithContentsOfFile(FileUtils::getInstance()->fullPathForFilename(file.c_str()).c_str());
	this->map = TMXTiledMap::createWithXML(str->getCString(), "");
	TMXLayer* obscatle = map->layerNamed("obscatle");
	//obscatle->removeFromParentAndCleanup(true);
	obscatle->setVisible(false);
	this->objGroup = map->getObjectGroup("Object");
	this->addChild(map, 0);
}

TMXTiledMap* MapLayer::getMap(){
	return this->map;
}
