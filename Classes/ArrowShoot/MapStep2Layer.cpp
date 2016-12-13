#include "MapStep2Layer.h"

bool MapStep2Layer::init()
{
	if (!Layer::create()) {
		return false;
	}
	std::string file = "MapStep2.tmx";
	addMap(file);
	return true;
}
