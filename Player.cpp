#include "Player.h"
#include "DxLib.h"
#include "Block.h"
#include <math.h>

//-----------定数宣言------------//
//レベルデザイン系
const int PLAYER_SPEED = 4;
const int TIME_AIR_DECREASE = 1;//AIRの減る速度
const int MOVE_WAIT = 5;
const int DRILL_RANGE = 7;
const int REVIVE_TIME = 3;
const int CHECK_AIR = 0;
const int JUMP_X = 50;
const int JUMP_Y = BLOCK_HEIGHT + 1;
const int AIR_RECOVERY_POINT = 20;
const double UP_TIME = 0.3;
const int BLOCK_POINT = 10;
const int SOLID_BLOCK_POINT = -20;
const int SOLID_AIR = 20;

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
const int CENTRAL_X = DRAW_WIDTH / 2 + 5;
const int CENTRAL_Y = DRAW_HEIGHT / 2;
const int UP_Y = 14 * DRAW_HEIGHT / SPRITE_SIZE;
const int DOWN_Y = 55 * DRAW_HEIGHT / SPRITE_SIZE;
const int LEFT_X = 13 * DRAW_WIDTH / SPRITE_SIZE;
const int RIGHT_X = 50 * DRAW_WIDTH / SPRITE_SIZE;

//-----------関数定義------------//

Player::Player( int x, int y, std::shared_ptr< Board > board ):
	_board( board ),
	_air( 100 ),
	_count( 0 ),
	_depth( 0 ),
	_life( 2 ),
	_score( 0 ),
	_level( 1 ),
	_x( x ),
	_y( y ),
	_up( 0 ),
	_death_anime_time( 0 ),
	_move_anime_time( 0 ),
	_direct( DIR_RIGHT ),
	_dead( false ),
	_standing( true ),
	_hitspace( false ) {
	_img_handle = LoadGraph( "Resource/NewCharacter.png", TRUE );
}

Player::~Player( ) {
	DeleteGraph( _img_handle );
}


void Player::update( ) {
	_count++;
	_vec_x = 0;
	_vec_y = 0;

	fall( );    //落下
	if ( !death( ) ) {
		if ( isStanding( ) ) {
			control( ); //操作
		}
		move( );    //移動
		ifAirRecover( ); //エア回復
		scoreBlock( ); //ブロックポイント
	} else {
		_erase_block = false;
	}

	//ブロックに乗っていない場合

	//深さ
	checkDepth( );
	decreaseAir( );
	if ( isCrushed( ) ||
		 isRunOutAir( ) ) {
		_dead = true;
	}

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

	if ( !isStanding( ) ) {
		setAct( ACT_FALL );
		return;
	}
	if ( _up > UP_TIME ) {
		_up = 0;
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



	//--------------キー操作------------//
	if ( CheckHitKey( KEY_INPUT_UP    ) == TRUE ) {
		_direct = DIR_UP;
	}
	if ( CheckHitKey( KEY_INPUT_DOWN  ) == TRUE ) {
		_direct = DIR_DOWN;
	}
	if ( CheckHitKey( KEY_INPUT_LEFT  ) == TRUE ) {
		_direct = DIR_LEFT;
		_vec_x += PLAYER_SPEED * -1;
	}
	if ( CheckHitKey( KEY_INPUT_RIGHT ) == TRUE ) {
		_direct = DIR_RIGHT;
		_vec_x += PLAYER_SPEED;
	}

	if ( CheckHitKey( KEY_INPUT_SPACE ) == TRUE ) {
		dig( );//掘る
	}
	//-----------------------------------//
}

void Player::actOnFall( ) {
	//落下中操作できない
	if ( _standing ) {
		setAct( ACT_STAND );
	}
}

void Player::actOnJump( ) {
	//数フレームかけて登る
	if ( _act_count > 10 ) {
		setAct( ACT_STAND );
	}
}

void Player::actOnDrill( ) {
	//数フレームかけて掘る
	if ( _act_count > 10 ) {
		setAct( ACT_STAND );
	}
}

void Player::actOnDeadAir( ) {
	if ( _act_count > 10 ) {
		//復活
		setAct( ACT_RESURRECTION );
	}
}

void Player::actOnDeadCrash( ) {
	if ( _act_count > 10 ) {
		//復活
		setAct( ACT_RESURRECTION );
	}
}

void Player::actOnResurrection( ) {
	_air = 100;
	_dead = false;
	setAct( ACT_STAND );
}

void Player::actOnDodgeBack( ) {
}

void Player::actOnGoal( ) {
}

void Player::actOnDodgeFront( ) {
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
	if ( !death( ) ) {
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
			tx = SPRITE_SIZE * ( _move_anime_time / MOVE_WAIT % MOVE_PATTERN );
			ty = SPRITE_SIZE * 19;
			break;
		case DIR_RIGHT:
			tx = SPRITE_SIZE * ( _move_anime_time / MOVE_WAIT % MOVE_PATTERN );
			ty = SPRITE_SIZE * 20;
			break;
		}
		DrawRectExtendGraph( x1, y1, x2, y2, tx, ty, SPRITE_SIZE, SPRITE_SIZE, _img_handle, TRUE );
	} else {
		drawDeathAnimation( camera_y );
	}
#if _DEBUG
	//当たり判定デバッグ用
	int left  = ( int )_x + LEFT_X;
	int right = ( int )_x + RIGHT_X;
	int up    = ( int )_y - camera_y + UP_Y;
	int down  = ( int )_y - camera_y + DOWN_Y;
	unsigned int color = GetColor( 255, 0, 0 );
	DrawBox( left, up, right, down, color, FALSE );
#endif
}


void Player::drawStand( int camera_y ) const {
}

void Player::drawFall( int camera_y ) const {
}

void Player::drawJump( int camera_y ) const {
}

void Player::drawDrill( int camera_y ) const {
}

void Player::drawDeadAir( int camera_y ) const {
}

void Player::drawDeadCrash( int camera_y ) const {
}

void Player::drawResurrection( int camera_y ) const {
}

void Player::drawDodgeBack( int camera_y ) const {
}

void Player::drawDodgeFront( int camera_y ) const {
}

void Player::drawGoal( int camera_y ) const {
}


void Player::drawDeathAnimation( int camera_y ) {
	_death_anime_time++;
	int _angel_time = ( int )( _death_anime_time - FRAME * TIME_ANIMATION );
	int anim = 0;
	if ( _death_anime_time / ( int )( FRAME * TIME_ANIMATION ) > 0 ) {
		anim = 7;
		eraseUpBlock( );
		_erase_block = false;
	}

	//酸欠
	int x1 = ( int )_x;
	int y1 = ( int )_y - camera_y;
	int x2 = x1 + DRAW_WIDTH;
	int y2 = y1 + DRAW_HEIGHT;
	int tx = 0;
	int ty = 0;

	if ( _air == CHECK_AIR ) {
		if ( _direct == DIR_LEFT ) {
			if (_death_anime_time <= 70){
				tx = SPRITE_SIZE * ( _death_anime_time / 10 % MOVE_PATTERN );
			}else{
			tx = SPRITE_SIZE * 7;
			}
			ty = SPRITE_SIZE * 4;
		} else {
			if (_death_anime_time <= 70){
				tx = SPRITE_SIZE * ( _death_anime_time / 10 % MOVE_PATTERN );
			}else{
				tx = SPRITE_SIZE * 7;
			}
			ty = SPRITE_SIZE * 5;
		}
	} else {
		//つぶれる
		if ( _direct == DIR_LEFT ) {
			if (_death_anime_time <= 20){
				tx = SPRITE_SIZE * ( _death_anime_time / 10 % 3 );
			}else{
				tx = SPRITE_SIZE * 2;
			}
			ty = SPRITE_SIZE * 11;
		} else {
			if (_death_anime_time <= 20){
				tx = SPRITE_SIZE * ( _death_anime_time / 10 % 3 );
			}else{
				tx = SPRITE_SIZE * 2;
			}
			ty = SPRITE_SIZE * 12;
		}

	}
	DrawRectExtendGraph( x1, y1, x2, y2, tx, ty, SPRITE_SIZE, SPRITE_SIZE, _img_handle, TRUE );

	//天使を描画
	if ( anim == 7 ) {
		int ANGEL_X = ( int )( 50 * sin( _angel_time * 0.1 ) );
		int ANGEL_Y = -_angel_time * 3;
		DrawRectExtendGraph( x1 + ANGEL_X, y1 + ANGEL_Y, x2 + ANGEL_X, y2 + ANGEL_Y, SPRITE_SIZE * ( _death_anime_time / 10 % 4 ), SPRITE_SIZE * 0, SPRITE_SIZE, SPRITE_SIZE, _img_handle, TRUE );
	}

	//復活
	if ( ( double )_angel_time / FRAME == REVIVE_TIME && _life > 0 ) {
		_life--;
		_air = 100;
		_dead = false;
		_death_anime_time = 0;
	}

}

bool Player::death( ) {
	return _dead;
}

int Player::getAir( ) {
	return _air;
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

int Player::getLevel( ) {
	return _level;
}

int Player::getY( ) {
	return ( int )_y;
}

bool Player::isStanding( ) const {
	return _standing;
}

void Player::control( ) {
	_vec_x = 0;

	if ( CheckHitKey( KEY_INPUT_UP ) == 1 ) {
		_direct = DIR_UP;
	}
	if ( CheckHitKey( KEY_INPUT_DOWN ) == 1 ) {
		_direct = DIR_DOWN;
	}
	if ( CheckHitKey( KEY_INPUT_LEFT ) == 1 ) {
		_direct = DIR_LEFT;
		_vec_x += PLAYER_SPEED * -1;
	}
	if ( CheckHitKey( KEY_INPUT_RIGHT ) == 1 ) {
		_direct = DIR_RIGHT;
		_vec_x += PLAYER_SPEED;
	}
	dig( );//掘る
}


void Player::move( ) {
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
		_move_anime_time = 0;
		_up = 0;
	}

	if ( _vec_x != 0 ) {
		_move_anime_time++;
		
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
				_up = 0;
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
				//登れるかチェック
				_up++;
				if ( _up >= ( int )( FRAME * UP_TIME ) ) {
					std::shared_ptr< Block > slant_block = _board->getBlock( check_x, central_y - BLOCK_HEIGHT );
					std::shared_ptr< Block > up_block    = _board->getBlock( central_x, central_y - BLOCK_HEIGHT );
					if ( ( !up_block    ||    up_block->getBlockID( ) == BLOCK_ID_AIR ) &&
						 ( !slant_block || slant_block->getBlockID( ) == BLOCK_ID_AIR ) ) {
						//登る
						_vec_y = -JUMP_Y;
						if ( left ) {
							_vec_x += JUMP_X * -1;
						} else {
							_vec_x += JUMP_X;
						}
					}
				}
			}
		} else {
			_up = 0;
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
	_vec_y = PLAYER_SPEED;
}

void Player::dig( ) {
	if ( CheckHitKey( KEY_INPUT_SPACE ) == TRUE ) {
		if ( !_hitspace ) {
			//連続は出来ない
			return;
		}
	} else {
		_hitspace = true;
		return;
	}
	_hitspace = false;

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
			_score += BLOCK_POINT;
		}
		if ( block->isErase( ) ) {
			if ( block->getBlockID( ) == BLOCK_ID_SOLID ) {
				//AIRが減る
				_air -= SOLID_AIR;
				_score += SOLID_BLOCK_POINT;
				if ( _score < 0 ) _score = 0;
			}
			if ( block->getBlockID( ) == BLOCK_ID_LEVEL ) {
				_level++;
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
			block->erase( );
			_air += AIR_RECOVERY_POINT;
			if ( _air > AIR_MAX ) {
				_air = AIR_MAX;
			}
		}
	}
}

void Player::eraseUpBlock( ) {
	if ( _erase_block ) {
		return;
	}
	//キャラクターの上のブロックを消す
	for ( int i = 0; i < 10; i++ ) {
		//3列分
		double check_y = _y + CENTRAL_Y - BLOCK_HEIGHT * i;
		double central_x = _x + CENTRAL_X;
		{//中央列
			double check_x = central_x;
			std::shared_ptr< Block > block = _board->getBlock( ( int )check_x, ( int )check_y );
			if ( block ) {
				if ( block->getBlockID( ) != BLOCK_ID_AIR ) {
					block->erase( );
				}
			}
		}
		
		{//左列
			double check_x = central_x - BLOCK_WIDTH;
			std::shared_ptr< Block > block = _board->getBlock( ( int )check_x, ( int )check_y );
			if ( block ) {
				if ( block->getBlockID( ) != BLOCK_ID_AIR ) {
					block->erase( );
				}
			}
		}
	
		{//右列
			double check_x = central_x + BLOCK_WIDTH;
			std::shared_ptr< Block > block = _board->getBlock( ( int )check_x, ( int )check_y );
			if ( block ) {
				if ( block->getBlockID( ) != BLOCK_ID_AIR ) {
					block->erase( );
				}
			}
		}
	}
}

void Player::decreaseAir( ) {
	_air--;
}

bool Player::isCrushed( ) const {
	//頭の位置にブロックが当たっているか確かめる
	bool result = false;
	double check_x = _x + CENTRAL_X;
	double check_y = _y + UP_Y;
	std::shared_ptr< Block > block = _board->getBlock( ( int )check_x, ( int )check_y );
	if ( block ) {
		if ( block->getBlockID( ) != BLOCK_ID_AIR ) {
			result = true;
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

void Player::scoreBlock( ) {
	double check_x = _x + CENTRAL_X;
	double check_y = _y + CENTRAL_Y;
	std::shared_ptr < Block > block = _board->getBlock( ( int )check_x, ( int )check_y );
	if ( block ) {
		if ( block->getBlockID( ) ) {
			_board->eraseBlock( block );
			_score += BLOCK_POINT;
		}
	}
}

void Player::setAct( ACT act ) {
	_act_count = 0;
	_act = act;
}