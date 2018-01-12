#pragma once
#include "map.h"
//ƒŒƒ”ƒFƒ‹4
class Map3 :public Map{
public:
	Map3();
	~Map3();
public:
	std::array< char, BLOCK_WIDTH_NUM * BLOCK_HEIGHT_NUM + 1 > getMap( int pattern );
private:
	std::array< std::array< char, BLOCK_WIDTH_NUM * BLOCK_HEIGHT_NUM + 1 >, MAX_PATTERN > _map;
};

