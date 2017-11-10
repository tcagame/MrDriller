#pragma once
#include <memory>

class Board;

class Player {
public:
	Player( int x, int y, std::shared_ptr< Board > board );
	virtual ~Player( );
public:
	void update( );
	void draw( );
	void drawDeathAnimation( );
	bool death( );
public://getån
	int getAir( );
private:
	int _air;
	int _img_handle;
	int _count;
	int _x;
	int _y;
	int _anime_time;
	std::shared_ptr< Board > _board;
};