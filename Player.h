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
	enum ACT {
		ACT_STAND,       //とまっているor歩く
		ACT_FALL,        //落ちる
		ACT_JUMP,        //のぼる
		ACT_DRILL,       //掘る
		ACT_DEAD_AIR,    //AIR不足で死亡
		ACT_DEAD_CRUSH,  //つぶれて死亡
		ACT_RESURRECTION,//復活
		ACT_DODGE_BACK,  //つぶれる回避(後ろにブロック)
		ACT_DODGE_FRONT,  //つぶれる回避(前にブロック)
		ACT_GOAL
	};
public:
	void update( );
	void draw( int camera_y );
	void drawDeathAnimation( int camera_y );
	bool death( );
	bool isStanding( ) const;
public://get系
	int getAir( );
	int getDepth( );
	int getLife( );
	int getScore( );
	int getLevel( );
	int getY( );
private:
	void act( );
	void actOnStand( );
	void actOnFall( );
	void actOnJump( );
	void actOnDrill( );
	void actOnDeadAir( );
	void actOnDeadCrash( );
	void actOnResurrection( );
	void actOnDodgeBack( );
	void actOnDodgeFront( );
	void actOnGoal( );
	void move( );
	void fall( );
	void dig( );
	void ifAirRecover( );
	void eraseUpBlock( );
	void decreaseAir( );
	void checkCrushed( );
	void checkDepth( );
	void control( );
	void scoreBlock( );
private:
	int _air;
	int _depth;
	int _life;
	int _score;
	int _img_handle;
	int _count;
	int _level;
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
	ACT _act;
};