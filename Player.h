#pragma once

#include <memory>
#include "define.h"
#include "Board.h"
#include "BlockIDList.h"

const int PLAYER_MAX_LIFE = 0;

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
	bool isGoal( ) const;
public://get系
	int getAir( ) const;
	int getDepth( ) const;
	int getLife( ) const;
	int getScore( ) const;
	int getX( ) const;
	int getY( ) const;
	ACT getAct( ) const;
private://Act
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
private://Draw
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
private://is
	bool isCrushed( ) const;
	bool isRunOutAir( ) const;
	bool isEnableJump( ) const;
	bool isDodgeBack( ) const;
	bool isDodgeFront( ) const;
private://other
	void move( );
	void fall( );
	void dig( );
	void ifAirRecover( );
	void eraseUpBlock( );
	void decreaseAir( );
	void setAct( ACT act );
	void checkDepth( );
	void checkAirDecreaseSpeed( );
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
	double _air_decrease_speed;
	bool _standing;
	bool _dig;
	bool _finished;
	bool _goal;
	bool _to_result_scene;
	enum DIR _direct;
	std::shared_ptr< Board > _board;
	ACT _act;
};