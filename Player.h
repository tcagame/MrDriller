#pragma once

#include <memory>
#include "define.h"
#include "Board.h"
#include "BlockIDList.h"


class Player {
public:
	Player( double x, double y, std::shared_ptr< Board > board );
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
	enum SE {
		SE_BLOCK_CRUSH,				//ブロック破壊
		SE_BLOCK_FALL_CRUSH,		//ブロック落ちて破壊
		SE_AIR_CAPSULE,				//エア
		SE_SOLID_REDUCE,			//お邪魔ブロックの削り
		SE_SOLID_CRUSH,				//お邪魔ブロックの破壊
		SE_LEVEL_CRUSH,				//岩盤破壊
		SE_AIR_LESS_THAN_THRITY,	//air<30
		SE_AIR_LESS_THAN_TEN,		//air<10
		SE_DEAD_AIR,				//酸欠死亡
		SE_DEAD_CRUSH,				//つぶれて死亡
		SE_ANGEL,					//天使
		SE_RESURRECTION,			//復活
		SE_xx1,
		SE_MENU_SELECT,				//メニュー選択
		SE_MENU_CLICK,				//メニュー決定
		SE_RESULT_NAMING,			//result画面で名前入力
		SE_xx2,
		SE_xx3
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
	int _img_handle;
	int _act_count;
	int _up_count;
	int _air_point;
	int _move_anim_count;
	double _x;
	double _y;
	double _vec_x;
	double _vec_y;
	double _target_x;
	double _target_y;
	bool _standing;
	bool _dig;
	bool _finished;
	bool _goal;
	bool _to_result_scene;
	enum DIR _direct;
	std::shared_ptr< Board > _board;
	std::array< int, 18 > _se;
	ACT _act;
};