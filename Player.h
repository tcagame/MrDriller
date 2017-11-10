#pragma once

#include <memory>
#include "Board.h"

class Player {
public:
	Player( int x, int y, std::shared_ptr< Board > board );
	virtual ~Player( );
public:
	void update( );
	void draw( );
	void drawDeathAnimation( );
	bool death( );
	bool isStanding( ) const;
public://getån
	int getAir( );
private:
	enum DIR {
		DIR_LEFT,
		DIR_RIGHT,
		DIR_UP,
		DIR_DOWN,
	};
private:
	void move( );
	void fall( );
private:
	int _air;
	int _img_handle;
	int _count;
	int _x;
	int _y;
	int _anime_time;
	bool _standing;
	enum DIR _direct;
	std::shared_ptr< Board > _board;
};