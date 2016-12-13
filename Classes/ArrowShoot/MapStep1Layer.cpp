#include "MapStep1Layer.h"

bool MapStep1Layer::init()
{
	if (!Layer::create()){
		return false;
	}
	std::string file = "Map.tmx";
	addMap(file);
	return true;
}
