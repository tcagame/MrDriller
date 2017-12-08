#pragma once
#include <array>
static const int BLOCK_WIDTH_NUM = 9;
static const int BLOCK_HEIGHT_NUM = 105;
static const int MAX_PATTERN = 3;

class Map {
public:
	Map( );
	virtual ~Map( );
public:
	virtual std::array< char, BLOCK_WIDTH_NUM * BLOCK_HEIGHT_NUM + 1 > getMap( int pattern ) = 0;
private:
	std::array< std::array< char, BLOCK_WIDTH_NUM * BLOCK_HEIGHT_NUM + 1 >, MAX_PATTERN > _map;
};