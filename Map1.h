#pragma once
#include "Map.h"
//ƒŒƒxƒ‹‚Q
class Map1 : public Map {
public:
	Map1( );
	~Map1( );
public:
	std::array< char, BLOCK_WIDTH_NUM * BLOCK_HEIGHT_NUM + 1 > getMap( int pattern );
private:
	std::array< std::array< char, BLOCK_WIDTH_NUM * BLOCK_HEIGHT_NUM + 1 >, MAX_PATTERN > _map;
};

