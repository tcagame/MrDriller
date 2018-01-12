#include "Player.h"
#include "DxLib.h"
#include "Block.h"
#include "Keyboard.h"
#include <math.h>

//-----------定数宣言------------//
//レベルデザイン系
const int PLAYER_SPEED = 4;
const double AIR_DECREASE_SPEED = 0.03;//AIRの減る速度
const int MOVE_WAIT = 5;
const int DRILL_RANGE = 7;
const int REVIVE_TIME = 300;
const int CHECK_AIR = 0;
const int DODGE_X = 32;
const int DODGE_SPEED = 1;
const int JUMP_SPEED_X = 4;
const int JUMP_SPEED_Y = 6;
const int JUMP_X = 60;
const int JUMP_Y = BLOCK_HEIGHT + 1;
const int AIR_RECOVERY_POINT = 20;
const int MAX_UP_COUNT = 20;
const int BLOCK_POINT = 10;
const int SOLID_BLOCK_POINT = -20;
const int SOLID_AIR = 20;
const int MAX_DLILL_COUNT = 30;
const int GOAL_LEVEL = 1;
const int To_Result_Scene_Time = 10;

//その他
const int AIR_MAX = 100;
const int MOVE_PATTERN = 8;
const int BLOCK_DEPTH = 5;
const int FRAME = 60;

//描画系
const double TIME_ANIMATION = 2.0;
const int SPRITE_SIZE = 64;
const int DRAW_WIDTH = 100;
const int DRAW_HEIGHT = 90;
//座標系
const int UP_Y = 14 * DRAW_HEIGHT / SPRITE_SIZE;
const int DOWN_Y = 55 * DRAW_HEIGHT / SPRITE_SIZE;
const int LEFT_X = 13 * DRAW_WIDTH / SPRITE_SIZE;
const int RIGHT_X = 50 * DRAW_WIDTH / SPRITE_SIZE;
const int CENTRAL_X = LEFT_X + ( RIGHT_X - LEFT_X ) / 2;
const int CENTRAL_Y = UP_Y + ( DOWN_Y - UP_Y ) / 2;



//-----------関数定義------------//

Player::Player( double x, double y, std::shared_ptr< Board > board ):
	_board( board ),
	_air( AIR_MAX ),
	_depth( 0 ),
	_life( 2 ),
	_score( 0 ),
	_x( x ),
	_y( y ),
	_air_point( 100 ),
	_up_count( 0 ),
	_move_anim_count( 0 ),
	_direct( DIR_RIGHT ),
	_to_result_scene( false ),
	_standing( true ),
	_finished( false ) {
	setAct( ACT_FALL );
	_img_handle = LoadGraph( "Resource/NewCharacter.png", TRUE );
}

Player::~Player( ) {
	DeleteGraph( _img_handle );
}


void Player::update( ) {
	_vec_x = 0;
	_vec_y = 0;

	fall( );    //落下
	act( );
	move( );    //移動
	//深さ
	checkDepth( );
	decreaseAir( );
	_act_count++;
}

void Player::act( ) {
	switch ( _act ) {
	case ACT_STAND:       //とまっているor歩く
		actOnStand( );
		break;
	case ACT_FALL:        //落ちる
		actOnFall( );
		break;
	case ACT_JUMP:        //のぼる
		actOnJump( );
		break;
	case ACT_DRILL:       //掘る
		actOnDrill( );
		break;
	case ACT_DEAD_AIR:    //AIR不足で死亡
		actOnDeadAir( );
		break;
	case ACT_DEAD_CRUSH:  //つぶれて死亡
		actOnDeadCrash( );
		break;
	case ACT_RESURRECTION://復活
		actOnResurrection( );
		break;
	case ACT_DODGE_BACK:  //つぶれる回避(後ろにブロック)
		actOnDodgeBack( );
		break;
	case ACT_DODGE_FRONT:  //つぶれる回避(前にブロック)
		actOnDodgeFront( );
		break;
	case ACT_GOAL:
		actOnGoal( );
		break;
	}
}

void Player::actOnStand( ) {
	_vec_x = 0;

	if ( isGoal( ) ) {
		setAct( ACT_GOAL );
		return;
	}

	if ( !isStanding( ) && !isGoal( ) ) {
		setAct( ACT_FALL );
		return;
	}
	if ( _up_count > MAX_UP_COUNT ) {
		_up_count = 0;
		_target_x = _x;
		_target_y = _y - JUMP_Y;
		if ( _direct == DIR_LEFT ) {
			_target_x -= JUMP_X;
		} else {
			_target_x += JUMP_X;
		}
		setAct( ACT_JUMP );
		return;
	}
	if ( isRunOutAir( ) ) {
		setAct( ACT_DEAD_AIR );
		return;
	}
	if ( isCrushed( ) ) {
		setAct( ACT_DEAD_CRUSH );
		return;
	}

	if ( isDodgeBack( ) ) {
		if ( _direct == DIR_LEFT ) {
			_target_x = _x - DODGE_X;
		} else {
			_target_x = _x + DODGE_X;
		}
		setAct( ACT_DODGE_BACK );
		return;
	}

	if ( isDodgeFront( ) ) {
		if ( _direct == DIR_LEFT ) {
			_target_x = _x + DODGE_X;
		} else {
			_target_x = _x - DODGE_X;
		}
		setAct( ACT_DODGE_FRONT );
		return;
	}


	//--------------キー操作------------//
	std::shared_ptr< Keyboard > key = Keyboard::getInstance( );
	if ( key->isHoldKey( KEY_INPUT_UP ) ) {
		_direct = DIR_UP;
	}
	if ( key->isHoldKey( KEY_INPUT_DOWN ) ) {
		_direct = DIR_DOWN;
	}
	if ( key->isHoldKey( KEY_INPUT_LEFT ) ) {
		_direct = DIR_LEFT;
	}
	if ( key->isHoldKey( KEY_INPUT_RIGHT ) ) {
		_direct = DIR_RIGHT;
	}
	if ( key->isHoldKey( KEY_INPUT_SPACE ) ) {
		setAct( ACT_DRILL );
		return;
	}
	if ( key->isHoldKey( KEY_INPUT_LEFT ) ) {
		_vec_x += PLAYER_SPEED * -1;
	}
	if ( key->isHoldKey( KEY_INPUT_RIGHT ) ) {
		_vec_x += PLAYER_SPEED;
	}

	//-----------------------------------//

	ifAirRecover( ); //エア回復
}

bool Player::isDodgeBack( ) const {
	double central_x = _x + CENTRAL_X;
	double check_y = _y + CENTRAL_Y;
	double check_left = _x + LEFT_X + 1;
	double check_right = _x + RIGHT_X - 1;
	bool result = false;
	std::shared_ptr< Block > block_left = _board->getBlock( ( int )check_left, ( int )check_y );
	std::shared_ptr< Block > block_right = _board->getBlock( ( int )check_right, ( int )check_y );
	std::shared_ptr< Block > block_central = _board->getBlock( ( int )central_x, ( int )check_y );
	if ( !block_central ) {
		if ( ( block_left  && _direct == DIR_RIGHT && block_left->getBlockID( ) != BLOCK_ID_AIR ) ||
			 ( block_right && _direct == DIR_LEFT  && block_right->getBlockID( ) != BLOCK_ID_AIR ) ) {
			result = true;
		}
	}
	return result;
}
bool Player::isDodgeFront( ) const {
	double central_x = _x + CENTRAL_X;
	double check_y = _y + CENTRAL_Y;
	double check_left = _x + LEFT_X + 1;
	double check_right = _x + RIGHT_X - 1;
	bool result = false;
	std::shared_ptr< Block > block_left = _board->getBlock( ( int )check_left, ( int )check_y );
	std::shared_ptr< Block > block_right = _board->getBlock( ( int )check_right, ( int )check_y );
	std::shared_ptr< Block > block_central = _board->getBlock( ( int )central_x, ( int )check_y );
	if ( !block_central ) {
		if ( ( block_left && _direct == DIR_LEFT  && block_left->getBlockID( )  != BLOCK_ID_AIR ) ||
			( block_right && _direct == DIR_RIGHT && block_right->getBlockID( ) != BLOCK_ID_AIR ) ) {
			result = true;
		}
	}
	return result;
}


void Player::actOnFall( ) {
	//落下中操作できない
	if ( isStanding( ) ) {
		setAct( ACT_STAND );
	}
	ifAirRecover( ); //エア回復
}

void Player::actOnJump( ) {
	if ( isRunOutAir( ) ) {
		setAct( ACT_DEAD_AIR );
		return;
	}
	if ( isCrushed( ) ) {
		setAct( ACT_DEAD_CRUSH );
		return;
	}

	//数フレームかけて登る
	_vec_x = _target_x - _x;
	_vec_y = _target_y - _y;

	if ( _vec_x > JUMP_SPEED_X ) {
		_vec_x = JUMP_SPEED_X;
	}
	if ( _vec_x < -JUMP_SPEED_X ) {
		_vec_x = -JUMP_SPEED_X;
	}
	if ( _vec_y > JUMP_SPEED_Y ) {
		_vec_y = JUMP_SPEED_Y;
	}
	if ( _vec_y < -JUMP_SPEED_Y ) {
		_vec_y = -JUMP_SPEED_Y;
	}


	if ( _vec_x == 0 &&
		 _vec_y == 0 ) {
		setAct( ACT_STAND );
	}
}

void Player::actOnDrill( ) {
	if ( isRunOutAir( ) ) {
		setAct( ACT_DEAD_AIR );
		return;
	}
	if ( isCrushed( ) ) {
		setAct( ACT_DEAD_CRUSH );
		return;
	}

	//数フレームかけて掘る
	_vec_x = 0;
	_vec_y = 0;
	if ( _act_count > MAX_DLILL_COUNT / 4 ) {
		dig( );//掘る
	}
	
	if ( _act_count > MAX_DLILL_COUNT ) {
		double check_x = 0;
		double check_y = 0;

 		switch ( _direct ) {
		case DIR_UP:
			//上の位置
			check_x = _x + CENTRAL_X;
			check_y = _y + UP_Y - DRILL_RANGE;
			break;
		case DIR_DOWN:
			//下の位置
			check_x = _x + CENTRAL_X;
			check_y = _y + DOWN_Y + DRILL_RANGE;
			break;
		case DIR_LEFT:
			//左の位置
			check_x = _x + LEFT_X - DRILL_RANGE;
			check_y = _y + CENTRAL_Y;
			break;
		case DIR_RIGHT:
			//右の位置
			check_x = _x + RIGHT_X + DRILL_RANGE;
			check_y = _y + CENTRAL_Y;
			break;
		}
		std::shared_ptr< Block > block = _board->getBlock( ( int )check_x, ( int )check_y );
		if ( !block ||
			 !block->isErase( ) ) {
			setAct( ACT_STAND );
		}
	}
}

void Player::actOnDeadAir( ) {
	eraseUpBlock( );
	if ( _act_count > REVIVE_TIME ) {
		//復活
		_life--;
		if ( _life >= 0 ) {
			setAct( ACT_RESURRECTION );
		} else {
			_finished = true;
		}
	}
}

void Player::actOnDeadCrash( ) {
	eraseUpBlock( );
	if ( _act_count > REVIVE_TIME ) {
		//復活
		_life--;
		if ( _life >= 0 ) {
			setAct( ACT_RESURRECTION );
		} else {
			_finished = true;
		}
	}
}

void Player::actOnResurrection( ) {
	_air = AIR_MAX;
	if ( _act_count > 30 ) {
		setAct( ACT_STAND );
	}
}

void Player::actOnDodgeBack( ) {
	if ( isRunOutAir( ) ) {
		setAct( ACT_DEAD_AIR );
		return;
	}
	if ( isCrushed( ) ) {
		setAct( ACT_DEAD_CRUSH );
		return;
	}
	//回避アニメーション待機
	//後ろに少し移動
	_vec_x = _target_x - _x;
	if ( _vec_x > DODGE_SPEED ) {
		_vec_x = DODGE_SPEED;
	}
	if ( _vec_x < -DODGE_SPEED ) {
		_vec_x = -DODGE_SPEED;
	}
	if ( _vec_x == 0 ) {
		setAct( ACT_STAND );
	}
}

void Player::actOnDodgeFront( ) {
	if ( isRunOutAir( ) ) {
		setAct( ACT_DEAD_AIR );
		return;
	}
	if ( isCrushed( ) ) {
		setAct( ACT_DEAD_CRUSH );
		return;
	}

	_vec_x = _target_x - _x;
	if ( _vec_x > DODGE_SPEED ) {
		_vec_x = DODGE_SPEED;
	}
	if ( _vec_x < -DODGE_SPEED ) {
		_vec_x = -DODGE_SPEED;
	}

	if ( _vec_x == 0 ) {
		setAct( ACT_STAND );
	}
}


void Player::actOnGoal( ) {
	_act_count++;
	if( _act_count >= To_Result_Scene_Time * FRAME ) {
		_to_result_scene = true;
	}
}

void Player::draw( int camera_y ) {
	switch ( _act ) {
	case ACT_STAND:       //とまっているor歩く
		drawStand( camera_y );
		break;
	case ACT_FALL:        //落ちる
		drawFall( camera_y );
		break;
	case ACT_JUMP:        //のぼる
		drawJump( camera_y );
		break;
	case ACT_DRILL:       //掘る
		drawDrill( camera_y );
		break;
	case ACT_DEAD_AIR:    //AIR不足で死亡
		drawDeadAir( camera_y );
		break;
	case ACT_DEAD_CRUSH:  //つぶれて死亡
		drawDeadCrash( camera_y );
		break;
	case ACT_RESURRECTION://復活
		drawResurrection( camera_y );
		break;
	case ACT_DODGE_BACK:  //つぶれる回避(後ろにブロック)
		drawDodgeBack( camera_y );
		break;
	case ACT_DODGE_FRONT:  //つぶれる回避(前にブロック)
		drawDodgeFront( camera_y );
		break;
	case ACT_GOAL:
		drawGoal( camera_y );
		break;
	}
	//x0、y0, x1, y1, tx, ty, tw, th, handle, trans(透過)
	//tx,tyは画像内の位置。tw,thは表示したい画像内のサイズ
#if _DEBUG
	//当たり判定デバッグ用
	int left  = ( int )_x + LEFT_X;
	int right = ( int )_x + RIGHT_X;
	int up    = ( int )_y - camera_y + UP_Y;
	int down  = ( int )_y - camera_y + DOWN_Y;
	unsigned int color = GetColor( 255, 0, 0 );
	//DrawCircle( ( int )_x + CENTRAL_X, ( int )_y + CENTRAL_Y - camera_y, 5, color, TRUE );
	//DrawCircle( right, up, 5, GetColor( 0, 255, 0 ), TRUE );
	//DrawCircle( left, up, 5, GetColor(0,0,255), TRUE );	
	DrawBox( left, up, right, down, color, FALSE );
	int central = ( int )_x + CENTRAL_X;
	DrawLine( central, up, central, down, color );
#endif
}


void Player::drawStand( int camera_y ) const {
	int x1 = ( int )_x;
	int x2 = ( int )( _x + DRAW_WIDTH );
	int y1 = ( int )( _y - camera_y);
	int y2 = ( int )( y1 + DRAW_HEIGHT );
	int tx = 0;
	int ty = 0;
	switch ( _direct ) {
	case DIR_UP:
		tx = SPRITE_SIZE * 0;
		ty = SPRITE_SIZE * 9;
		break;
	case DIR_DOWN:
		tx = SPRITE_SIZE * 0;
		ty = SPRITE_SIZE * 6;
		break;
	case DIR_LEFT:
		tx = SPRITE_SIZE * ( _move_anim_count / MOVE_WAIT % MOVE_PATTERN );
		ty = SPRITE_SIZE * 19;
		break;
	case DIR_RIGHT:
		tx = SPRITE_SIZE * ( _move_anim_count / MOVE_WAIT % MOVE_PATTERN );
		ty = SPRITE_SIZE * 20;
		break;
	}
	DrawRectExtendGraph( x1, y1, x2, y2, tx, ty, SPRITE_SIZE, SPRITE_SIZE, _img_handle, TRUE );
}

void Player::drawFall( int camera_y ) const {
	int x1 = ( int )_x;
	int x2 = ( int )( _x + DRAW_WIDTH );
	int y1 = ( int )( _y - camera_y);
	int y2 = ( int )( y1 + DRAW_HEIGHT );
	int tx = SPRITE_SIZE * 0;
	int ty = SPRITE_SIZE * 1;

	DrawRectExtendGraph( x1, y1, x2, y2, tx, ty, SPRITE_SIZE, SPRITE_SIZE, _img_handle, TRUE );
}

void Player::drawJump( int camera_y ) const {
	const int ANIM_PATTERN = 8;
	int pattern = ANIM_PATTERN - ( int )( abs( _y - _target_y ) ) / ( JUMP_Y / ANIM_PATTERN );
	if ( pattern < 0 ) {
		pattern = 0;
	}
	if ( pattern > ANIM_PATTERN - 1 ) {
		pattern = ANIM_PATTERN - 1;
	}
	int x1 = ( int )_x;
	int x2 = ( int )( _x + DRAW_WIDTH );
	int y1 = ( int )( _y - camera_y);
	int y2 = ( int )( y1 + DRAW_HEIGHT );
	int tx = SPRITE_SIZE * pattern;
	int ty = 0;
	switch ( _direct ) {
	case DIR_LEFT:
		ty = SPRITE_SIZE * 2;
		break;
	case DIR_RIGHT:
		ty = SPRITE_SIZE * 3;
		break;
	}

	DrawRectExtendGraph( x1, y1, x2, y2, tx, ty, SPRITE_SIZE, SPRITE_SIZE, _img_handle, TRUE );
}

void Player::drawDrill( int camera_y ) const {
	const int ANIM_PATTERN = 8;
	int pattern = _act_count / ( MAX_DLILL_COUNT / ANIM_PATTERN );
	if ( pattern >= ANIM_PATTERN ) {
		pattern = ANIM_PATTERN - 1;
	}
	int x1 = ( int )_x;
	int x2 = ( int )( _x + DRAW_WIDTH );
	int y1 = ( int )( _y - camera_y);
	int y2 = ( int )( y1 + DRAW_HEIGHT );
	int tx = SPRITE_SIZE * pattern;
	int ty = 0;
	switch ( _direct ) {
	case DIR_UP:
		ty = SPRITE_SIZE * 9;
		break;
	case DIR_DOWN:
		ty = SPRITE_SIZE * 6;
		break;
	case DIR_LEFT:
		ty = SPRITE_SIZE * 7;
		break;
	case DIR_RIGHT:
		ty = SPRITE_SIZE * 8;
		break;
	}
	DrawRectExtendGraph( x1, y1, x2, y2, tx, ty, SPRITE_SIZE, SPRITE_SIZE, _img_handle, TRUE );
}

void Player::drawDeadAir( int camera_y ) const {
	int _angel_time = ( int )( _act_count - FRAME * TIME_ANIMATION );
	int anim = 0;
	if ( _act_count / ( int )( FRAME * TIME_ANIMATION ) > 0 ) {
		anim = 7;
	}

	//酸欠
	int x1 = ( int )_x;
	int y1 = ( int )_y - camera_y;
	int x2 = x1 + DRAW_WIDTH;
	int y2 = y1 + DRAW_HEIGHT;
	int tx = 0;
	int ty = 0;

	if ( _act_count <= 70 ){
		tx = SPRITE_SIZE * ( _act_count / 10 % MOVE_PATTERN );
	}else{
		tx = SPRITE_SIZE * 7;
	}
	if ( _direct == DIR_LEFT ) {
		ty = SPRITE_SIZE * 4;
	} else {
		ty = SPRITE_SIZE * 5;
	}
	
	
	DrawRectExtendGraph( x1, y1, x2, y2, tx, ty, SPRITE_SIZE, SPRITE_SIZE, _img_handle, TRUE );

	//天使を描画
	if ( anim == 7 ) {
		int ANGEL_X = ( int )( 50 * sin( _angel_time * 0.1 ) );
		int ANGEL_Y = -_angel_time * 3;
		DrawRectExtendGraph( x1 + ANGEL_X, y1 + ANGEL_Y, x2 + ANGEL_X, y2 + ANGEL_Y, SPRITE_SIZE * ( _act_count / 10 % 4 ), SPRITE_SIZE * 0, SPRITE_SIZE, SPRITE_SIZE, _img_handle, TRUE );
	}

}

void Player::drawDeadCrash( int camera_y ) const {
	int _angel_time = ( int )( _act_count - FRAME * TIME_ANIMATION );
	int anim = 0;
	if ( _act_count / ( int )( FRAME * TIME_ANIMATION ) > 0 ) {
		anim = 7;
	}

	int x1 = ( int )_x;
	int y1 = ( int )_y - camera_y;
	int x2 = x1 + DRAW_WIDTH;
	int y2 = y1 + DRAW_HEIGHT;
	int tx = 0;
	int ty = 0;

	if ( _act_count <= 20 ){
		tx = SPRITE_SIZE * ( _act_count / 10 % 3 );
	}else{
		tx = SPRITE_SIZE * 2;
	}
	if ( _direct == DIR_LEFT ) {
		ty = SPRITE_SIZE * 11;
	} else {
		ty = SPRITE_SIZE * 12;
	}
	
	DrawRectExtendGraph( x1, y1, x2, y2, tx, ty, SPRITE_SIZE, SPRITE_SIZE, _img_handle, TRUE );

	//天使を描画
	if ( anim == 7 ) {
		int ANGEL_X = ( int )( 50 * sin( _angel_time * 0.1 ) );
		int ANGEL_Y = -_angel_time * 3;
		DrawRectExtendGraph( x1 + ANGEL_X, y1 + ANGEL_Y, x2 + ANGEL_X, y2 + ANGEL_Y, SPRITE_SIZE * ( _act_count / 10 % 4 ), SPRITE_SIZE * 0, SPRITE_SIZE, SPRITE_SIZE, _img_handle, TRUE );
	}
}

void Player::drawResurrection( int camera_y ) const {
	const int ANIM_PATTERN = 3;
	const int WAIT = 10;
	int x1 = ( int )_x;
	int y1 = ( int )_y - camera_y;
	int x2 = x1 + DRAW_WIDTH;
	int y2 = y1 + DRAW_HEIGHT;
	int tx = SPRITE_SIZE * ( _act_count / WAIT % ANIM_PATTERN );
	int ty = SPRITE_SIZE * 10;
	DrawRectExtendGraph( x1, y1, x2, y2, tx, ty, SPRITE_SIZE, SPRITE_SIZE, _img_handle, TRUE );
}

void Player::drawDodgeBack( int camera_y ) const {
	const int ANIM_PATTERN = 3;
	int pattern = ANIM_PATTERN - ( int )( abs( abs( _target_x - _x ) - 1 ) ) * ANIM_PATTERN / DODGE_X - 1;
	int x1 = ( int )_x;
	int y1 = ( int )_y - camera_y;
	int x2 = x1 + DRAW_WIDTH;
	int y2 = y1 + DRAW_HEIGHT;
	int tx = SPRITE_SIZE * pattern;
	int ty = 0;
	if ( _direct == DIR_LEFT ) {
		ty = SPRITE_SIZE * 13;
	} else {
		ty = SPRITE_SIZE * 14;
	}
	DrawRectExtendGraph( x1, y1, x2, y2, tx, ty, SPRITE_SIZE, SPRITE_SIZE, _img_handle, TRUE );
}

void Player::drawDodgeFront( int camera_y ) const {
	const int ANIM_PATTERN = 3;
	int pattern = ANIM_PATTERN - ( int )( abs( abs( _target_x - _x ) - 1 ) ) * ANIM_PATTERN / DODGE_X - 1;
	int x1 = ( int )_x;
	int y1 = ( int )_y - camera_y;
	int x2 = x1 + DRAW_WIDTH;
	int y2 = y1 + DRAW_HEIGHT;
	int tx = SPRITE_SIZE * pattern;
	int ty = 0;
	if ( _direct == DIR_LEFT ) {
		ty = SPRITE_SIZE * 15;
	} else {
		ty = SPRITE_SIZE * 16;
	}
	DrawRectExtendGraph( x1, y1, x2, y2, tx, ty, SPRITE_SIZE, SPRITE_SIZE, _img_handle, TRUE );
}

void Player::drawGoal( int camera_y ) const {
	const int ANIM_PATTERN = 8;
	const int ANIM_WAIT = 10;
	int pattern = _act_count / ANIM_WAIT % ANIM_PATTERN;
	int x1 = ( int )_x;
	int y1 = ( int )_y - camera_y;
	int x2 = x1 + DRAW_WIDTH;
	int y2 = y1 + DRAW_HEIGHT;
	int tx = SPRITE_SIZE * pattern;
	int ty = SPRITE_SIZE * 21;
	DrawRectExtendGraph( x1, y1, x2, y2, tx, ty, SPRITE_SIZE, SPRITE_SIZE, _img_handle, TRUE );
}

bool Player::isDead( ) const {
	return _act == ACT_DEAD_AIR || _act == ACT_DEAD_CRUSH;
}

int Player::getAir( ) {
	return ( int )_air;
}

int Player::getDepth( ) {
	return _depth;
}

int Player::getLife( ) {
	return _life;
}

int Player::getScore( ) {
	return _score;
}

int Player::getX( ) {
	return ( int )_x;
}

int Player::getY( ) {
	return ( int )_y;
}

bool Player::isStanding( ) const {
	return _standing;
}

bool Player::isFinished( ) const {
	return _finished;
}

bool Player::isGoal( ) const {
	return _goal;
}

bool Player::isResultScene( ) const {
	return _to_result_scene;
}

void Player::move( ) {
	if ( _act == ACT_JUMP ) {
		_x += _vec_x;
		_y += _vec_y;
		return;
	}
	_standing = false;
	if ( _vec_y > 0 ) {
		//下ブロックに当たる
		int check_left = ( int )_x + LEFT_X + 1;
		int check_right = ( int )_x + RIGHT_X - 1;
		int check_y = ( int )( _y + DOWN_Y + _vec_y );

		//落下場所にブロックが存在しているかチェック
		std::shared_ptr< Block > block_left = _board->getBlock( check_left, check_y );
		std::shared_ptr< Block > block_right = _board->getBlock( check_right, check_y );
		if ( block_left || block_right ) {
			std::shared_ptr< Block > col_block = block_left;
			if ( !col_block ) {
				col_block = block_right;
			} else {
				if ( col_block->getBlockID( ) == BLOCK_ID_AIR && block_right ) {
					col_block = block_right;
				}
			}
			if ( col_block->getBlockID( ) != BLOCK_ID_AIR ) {
				_standing = true;
				double target = col_block->getY( ) - DOWN_Y - 1;

				_vec_y = target - _y;
			}
		}
	}

	
	if ( _vec_x == 0 ) {
		//移動キーを押していない
		_move_anim_count = 0;
		_up_count = 0;
	}

	if ( _vec_x != 0 ) {
		_move_anim_count++;
		
		//チェック座標
		bool left = true;
		int adjust_x = LEFT_X;
		if ( _vec_x > 0 ) {
			left = false;
			adjust_x = RIGHT_X;
		}
		int central_x = ( int )_x + CENTRAL_X;
		int central_y = ( int )_y + CENTRAL_Y;
		int check_x = ( int )( _x + adjust_x + _vec_x );
		int up_y = ( int )_y + UP_Y;
		int down_y = ( int )_y + DOWN_Y;

		//キャラクターのx:端y:中央 +vec
		//ブロックが存在するかチェック
		std::shared_ptr< Block > block1 = _board->getBlock( check_x, up_y );
		std::shared_ptr< Block > block2 = _board->getBlock( check_x, down_y );
		if ( block1 || block2 ) {//ブロックに当たった場合
			std::shared_ptr< Block > col_block = block2;
			if ( !col_block ) {
				col_block = block1;
			}
			if ( col_block->getBlockID( ) == BLOCK_ID_AIR ) {
				//横のブロックがエアー
				_up_count = 0;
			} else {
				//横のブロックが通常
				//移動しない
				double target = 0;
				if ( left ) {
					target = col_block->getX( ) + BLOCK_WIDTH - LEFT_X;
				} else {
					target = col_block->getX( ) - RIGHT_X;
				}
				_vec_x = target - _x;
				if ( isEnableJump( ) ) {
					_up_count++;
				} else {
					_up_count = 0;
				}
			}
		} else {
			_up_count = 0;
		}
		//画面端
		if ( _vec_x < 0 ) {
			if ( check_x + _vec_x < 0 ) {
				_vec_x = 0 - check_x;
			}
		}
		if ( _vec_x > 0 ) {
			if ( check_x + _vec_x > 900 ) {
				_vec_x = 900 - check_x;
			}
		}
	}

	//移動
	_x += _vec_x;
	_y += _vec_y;
}


void Player::fall( ) {
	if ( _act != ACT_FALL &&
		 _act != ACT_STAND ) {
		return;
	}
	_vec_y = PLAYER_SPEED;
}

void Player::dig( ) {
	if ( _dig ) {
		return;
	}
	_dig = true;

	double check_x = 0;
	double check_y = 0;

 	switch ( _direct ) {
	case DIR_UP:
		//上の位置
		check_x = _x + CENTRAL_X;
		check_y = _y + UP_Y - DRILL_RANGE;
		break;
	case DIR_DOWN:
		//下の位置
		check_x = _x + CENTRAL_X;
		check_y = _y + DOWN_Y + DRILL_RANGE;
		break;
	case DIR_LEFT:
		//左の位置
		check_x = _x + LEFT_X - DRILL_RANGE;
		check_y = _y + CENTRAL_Y;
		break;
	case DIR_RIGHT:
		//右の位置
		check_x = _x + RIGHT_X + DRILL_RANGE;
		check_y = _y + CENTRAL_Y;
		break;
	}

	std::shared_ptr < Block > block = _board->getBlock( ( int )check_x, ( int )check_y );
	//ポインタが存在する場合true
	if ( block && !block->isErase( ) ) {
		if ( block->getBlockID( ) != BLOCK_ID_AIR ) {
			_board->eraseBlock( block );
		}
		if ( block->getBlockID( ) != BLOCK_ID_SOLID ) {
			_score += BLOCK_POINT; //ブロックのスコア
		}
		if ( block->isErase( ) ) {
			if ( block->getBlockID( ) == BLOCK_ID_SOLID ) {
				//AIRが減る
				_air -= SOLID_AIR;
				_score += SOLID_BLOCK_POINT;
				if ( _score < 0 ) _score = 0;
			}
			if ( block->getBlockID( ) == BLOCK_ID_LEVEL && _board->getLevel() == GOAL_LEVEL ) {
				_goal = true;
			}
		}
	}
}

void Player::ifAirRecover( ) {
	double check_x = _x + CENTRAL_X;
	double check_y = _y + CENTRAL_Y;
	std::shared_ptr < Block > block = _board->getBlock( ( int )check_x, ( int )check_y );
	if ( block ) {
		if ( block->getBlockID( ) == BLOCK_ID_AIR ) {
			if ( !block->isErase( ) ) {
				block->erase( );
				_air += AIR_RECOVERY_POINT;
				_score += _air_point;
				_air_point += 100;
				if ( _air > AIR_MAX ) {
					_air = AIR_MAX;
				}
			}
		}
	}
}

void Player::eraseUpBlock( ) {
	if ( _dig ) {
		return;
	}
	//3列分削除
	_dig = true;
	double central_x = _x + CENTRAL_X;
	double central_y = _y + CENTRAL_Y;

	//中央列
	_board->eraseColumnBlockUp( ( int )central_x              , ( int )central_y );
	//左列
	_board->eraseColumnBlockUp( ( int )central_x - BLOCK_WIDTH, ( int )central_y );
	//右列
	_board->eraseColumnBlockUp( ( int )central_x + BLOCK_WIDTH, ( int )central_y );
}

void Player::decreaseAir( ) {
	if ( isDead( ) ) {
		return;
	}
	if ( !isGoal( ) ) {
		_air -= AIR_DECREASE_SPEED;
	}
	if ( _air <= 0 ) {
		_air = 0;
	}
}

bool Player::isCrushed( ) const {
	//頭の位置にブロックが当たっているか確かめる
	double central_x = _x + CENTRAL_X;
	double check_y = _y + CENTRAL_Y;
	double check_left = _x + LEFT_X + 1;
	double check_right = _x + RIGHT_X - 1;
	bool result = false;
	std::shared_ptr< Block > block_left = _board->getBlockNow( ( int )check_left, ( int )check_y );
	std::shared_ptr< Block > block_right = _board->getBlockNow( ( int )check_right, ( int )check_y );
	std::shared_ptr< Block > block_central = _board->getBlockNow( ( int )central_x, ( int )check_y );
	if ( block_central ) {
		if ( block_left || block_right ) {
			if ( block_central->getBlockID( ) != BLOCK_ID_AIR ) {
				result = true;
			}
		}
	}
	return result;
}

bool Player::isRunOutAir( ) const {
	return _air <= 0;
}

void Player::checkDepth( ) {
	_depth = ( int )_y / BLOCK_HEIGHT * BLOCK_DEPTH + BLOCK_DEPTH - 20;
}

void Player::setAct( ACT act ) {
	_dig = false;
	_vec_x = 0;
	_act_count = 0;
	_act = act;
}

bool Player::isEnableJump( ) const {
	//登れるかチェック
	bool result = false;
	int adjust_x = 0;
	if ( _direct == DIR_RIGHT ) {
		adjust_x += BLOCK_WIDTH;
	} else {
		adjust_x -= BLOCK_WIDTH;
	}
	int central_x = ( int )_x + CENTRAL_X;
	int central_y = ( int )_y + CENTRAL_Y;

	std::shared_ptr< Block > slant_block = _board->getBlock( central_x + adjust_x, central_y - BLOCK_HEIGHT );
	std::shared_ptr< Block > up_block    = _board->getBlock( central_x           , central_y - BLOCK_HEIGHT );
	if ( ( !up_block    ||    up_block->getBlockID( ) == BLOCK_ID_AIR ) &&
		 ( !slant_block || slant_block->getBlockID( ) == BLOCK_ID_AIR ) ) {
		result = true;
	}
	return result;
}