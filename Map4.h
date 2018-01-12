#pragma once
#include "map.h"
//ƒŒƒ”ƒFƒ‹5
class Map4 : public Map{
public:
	Map4( );
	~Map4( );
public:
	std::array< char, BLOCK_WIDTH_NUM * BLOCK_HEIGHT_NUM + 1 >getMap( int pattern );
private:
	std::array< std::array< char, BLOCK_WIDTH_NUM * BLOCK_HEIGHT_NUM + 1 >, MAX_PATTERN > _map;
};

