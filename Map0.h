#pragma once
#include "Map.h"

class Map0 : public Map {
public:
	Map0( );
	virtual ~Map0( );
public:
	std::array< char, BLOCK_WIDTH_NUM * BLOCK_HEIGHT_NUM + 1 > getMap( int pattern );
private:
	std::array< std::array< char, BLOCK_WIDTH_NUM * BLOCK_HEIGHT_NUM + 1 >, MAX_PATTERN > _map;
};

