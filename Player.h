#pragma once

#include <memory>
#include "Board.h"
#include "BlockIDList.h"


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
	int getDepth( );
	int getLife( );
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
	void dig( );
	void ifAirRecover( );
private:
	int _air;
	int _depth;
	int _life;
	int _img_handle;
	int _count;
	int _x;
	int _y;
	int _death_anime_time;
	int _move_anime_time;
	bool _standing;
	bool _hitspace;
	enum DIR _direct;
	std::shared_ptr< Board > _board;
};