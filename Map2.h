#pragma once
#include "Map.h"
//ƒŒƒxƒ‹3
class Map2 :public Map{
public:
	Map2();
	~Map2();
public:
	std::array< char, BLOCK_WIDTH_NUM * BLOCK_HEIGHT_NUM + 1 > getMap( int pattern );
private:
	std::array< std::array< char, BLOCK_WIDTH_NUM * BLOCK_HEIGHT_NUM + 1 >, MAX_PATTERN > _map;
};

