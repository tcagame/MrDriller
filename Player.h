#pragma once

#include <memory>
#include "define.h"
#include "Board.h"
#include "BlockIDList.h"

const int PLAYER_MAX_LIFE = 2;

class Player {
public:
	Player( int x, int y, std::shared_ptr< Board > board );
	virtual ~Player( );
public:
	enum ACT {
		ACT_STAND,			//とまっているor歩く
		ACT_FALL,			//落ちる
		ACT_JUMP,			//のぼる
		ACT_DRILL,			//掘る
		ACT_DEAD_AIR,		//AIR不足で死亡
		ACT_DEAD_CRUSH,		//つぶれて死亡
		ACT_RESURRECTION,	//復活
		ACT_DODGE_BACK,		//つぶれる回避(後ろにブロック)
		ACT_DODGE_FRONT,	//つぶれる回避(前にブロック)
		ACT_GOAL			//ゴール
	};
public:
	void update( );
	void draw( int camera_y );
public:
	bool isDead( ) const;
	bool isStanding( ) const;
	bool isFinished( ) const;
	bool isResultScene( ) const;
	bool isGoal( ) const;
public://get系
	int getAir( );
	int getDepth( );
	int getLife( );
	int getScore( );
	int getX( );
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
	void drawStand( int camera_y ) const;
	void drawFall( int camera_y ) const;
	void drawJump( int camera_y ) const;
	void drawDrill( int camera_y ) const;
	void drawDeadAir( int camera_y ) const;
	void drawDeadCrash( int camera_y ) const;
	void drawResurrection( int camera_y ) const;
	void drawDodgeBack( int camera_y ) const;
	void drawDodgeFront( int camera_y ) const;
	void drawGoal( int camera_y ) const;
	void move( );
	void fall( );
	void dig( );
	void ifAirRecover( );
	void eraseUpBlock( );
	void decreaseAir( );
	bool isCrushed( ) const;
	bool isRunOutAir( ) const;
	bool isEnableJump( ) const;
	bool isDodgeBack( ) const;
	bool isDodgeFront( ) const;
	void checkDepth( );
	void setAct( ACT act );
private:
	double _air;
	int _depth;
	int _life;
	int _score;
	int _act_count;
	int _up_count;
	int _air_point;
	int _move_anim_count;
	int _x;
	int _y;
	int _vec_x;
	int _vec_y;
	int _target_x;
	int _target_y;
	bool _standing;
	bool _dig;
	bool _finished;
	bool _goal;
	bool _to_result_scene;
	enum DIR _direct;
	std::shared_ptr< Board > _board;
	ACT _act;
};