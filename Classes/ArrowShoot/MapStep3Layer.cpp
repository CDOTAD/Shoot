#include "MapStep3Layer.h"

bool MapStep3Layer::init()
{
	if (!Layer::create()) {
		return false;
	}
	std::string file = "MapStep3.tmx";
	addMap(file);
	return true;
}
