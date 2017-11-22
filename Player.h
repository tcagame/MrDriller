#pragma once

#include <memory>
#include "define.h"
#include "Board.h"
#include "BlockIDList.h"


class Player {
public:
	Player( int x, int y, std::shared_ptr< Board > board );
	virtual ~Player( );
public:
	void update( );
	void draw( int camera_y );
	void drawDeathAnimation( int camera_y );
	bool death( );
	bool isStanding( ) const;
public://getån
	int getAir( );
	int getDepth( );
	int getLife( );
	int getScore( );
	int getY( );
private:
	void move( );
	void fall( );
	void dig( );
	void ifAirRecover( );
	void eraseUpBlock( );
	void decreaseAir( );
	void checkCrushed( );
	void checkDepth( );
	void control( );
private:
	int _air;
	int _depth;
	int _life;
	int _score;
	int _img_handle;
	int _count;
	double _x;
	double _y;
	double _vec_x;
	double _vec_y;
	int _up;
	int _death_anime_time;
	int _move_anime_time;
	bool _dead;
	bool _standing;
	bool _hitspace;
	bool _erase_block;
	enum DIR _direct;
	std::shared_ptr< Board > _board;
};