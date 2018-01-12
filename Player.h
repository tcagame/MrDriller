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
		ACT_STAND,			//�Ƃ܂��Ă���or����
		ACT_FALL,			//������
		ACT_JUMP,			//�̂ڂ�
		ACT_DRILL,			//�@��
		ACT_DEAD_AIR,		//AIR�s���Ŏ��S
		ACT_DEAD_CRUSH,		//�Ԃ�Ď��S
		ACT_RESURRECTION,	//����
		ACT_DODGE_BACK,		//�Ԃ����(���Ƀu���b�N)
		ACT_DODGE_FRONT,	//�Ԃ����(�O�Ƀu���b�N)
		ACT_GOAL			//�S�[��
	};
	enum SE {
		SE_BLOCK_CRUSH,				//�u���b�N�j��
		SE_BLOCK_FALL_CRUSH,		//�u���b�N�����Ĕj��
		SE_AIR_CAPSULE,				//�G�A
		SE_SOLID_REDUCE,			//���ז��u���b�N�̍��
		SE_SOLID_CRUSH,				//���ז��u���b�N�̔j��
		SE_LEVEL_CRUSH,				//��Քj��
		SE_AIR_LESS_THAN_THRITY,	//air<30
		SE_AIR_LESS_THAN_TEN,		//air<10
		SE_DEAD_AIR,				//�_�����S
		SE_DEAD_CRUSH,				//�Ԃ�Ď��S
		SE_ANGEL,					//�V�g
		SE_RESURRECTION,			//����
		SE_xx1,
		SE_MENU_SELECT,				//���j���[�I��
		SE_MENU_CLICK,				//���j���[����
		SE_RESULT_NAMING,			//result��ʂŖ��O����
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
public://get�n
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