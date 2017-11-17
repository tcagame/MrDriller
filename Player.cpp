#include "Player.h"
#include "DxLib.h"
#include <math.h>

//定数宣言
const int TIME_AIR_DECREASE = 1;//AIRの減る速度
const int FRAME = 60;
const int PLAYER_SIZE_X = 27;
const int PLAYER_SIZE_Y = 27;
const int PLAYER_SPEED = 4;
const int DRAW_WIDTH = 100;
const int DRAW_HEIGHT = 90;
const int CHARACTER_WIDTH = 70;
const int CHARACTER_HEIGHT = 60;
const int ADJUST_X = DRAW_WIDTH / 2 + 5;
const int ADJUST_Y = DRAW_HEIGHT / 2;
const int BLOCK_DEPTH = 5;
const int MOVE_WAIT = 5;
const int MOVE_PATTERN = 4;
const int DRILL_RANGE = 7;
const int REVIVE_TIME = 3;
const int CHECK_AIR = 0;
const int JUMP_X = 50;
const int JUMP_Y = BLOCK_HEIGHT + 10;
const int AIR_RECOVERY_POINT = 20;
const int AIR_MAX = 100;
const double UP_TIME = 0.3;
const double TIME_ANIMATION = 0.5;


Player::Player( int x, int y, std::shared_ptr< Board > board ):
	_board( board ),
	_air( 100 ),
	_count( 0 ),
	_depth( 0 ),
	_life( 2 ),
	_score( 0 ),
	_x( x ),
	_y( y ),
	_up( 0 ),
	_death_anime_time( 0 ),
	_move_anime_time( 0 ),
	_direct( DIR_RIGHT ),
	_standing( true ),
	_hitspace( false ) {
	_img_handle = LoadGraph( "Resource/Character.png", TRUE );
}

Player::~Player( ) {
	DeleteGraph( _img_handle );
}


void Player::update( ) {
	_count++;
	if ( _count % ( FRAME * TIME_AIR_DECREASE ) == 0 && _air > CHECK_AIR ) {
		_air--;
	}

	if ( !death( ) ) {
		//移動
		move( );
		//エア回復
		ifAirRecover( );
		//掘る
		dig( );
	} else {
		_erase_block = false;
	}
	//ブロックに乗っていない場合
	fall( );

	//深さ
	_depth = _y / BLOCK_HEIGHT * BLOCK_DEPTH;
}

void Player::draw( int camera_y ) {
	//x0、y0, x1, y1, tx, ty, tw, th, handle, trans(透過)
	//tx,tyは画像内の位置。tw,thは表示したい画像内のサイズ
	if ( !death( ) ) {
		int x1 = _x;
		int x2 = _x + DRAW_WIDTH;
		int y1 = _y - camera_y;
		int y2 =  y1 + DRAW_HEIGHT;
		if ( _direct == DIR_LEFT ) {
			DrawRectExtendGraph( x1, y1, x2, y2, PLAYER_SIZE_X * ( _move_anime_time / MOVE_WAIT % MOVE_PATTERN ), PLAYER_SIZE_Y * 5, PLAYER_SIZE_X, PLAYER_SIZE_Y, _img_handle, TRUE );
		} else if ( _direct == DIR_RIGHT ) {
			DrawRectExtendGraph( x1, y1, x2, y2, PLAYER_SIZE_X * ( _move_anime_time / MOVE_WAIT % MOVE_PATTERN ), PLAYER_SIZE_Y * 4, PLAYER_SIZE_X, PLAYER_SIZE_Y, _img_handle, TRUE );
		} else if ( _direct == DIR_UP ) {
			DrawRectExtendGraph( x1, y1, x2, y2, PLAYER_SIZE_X * 0, PLAYER_SIZE_Y * 3, PLAYER_SIZE_X, PLAYER_SIZE_Y, _img_handle, TRUE );
		} else if ( _direct == DIR_DOWN ) {
			DrawRectExtendGraph( x1, y1, x2, y2, PLAYER_SIZE_X * 0, PLAYER_SIZE_Y * 0, PLAYER_SIZE_X, PLAYER_SIZE_Y, _img_handle, TRUE );
		}
	} else {
		drawDeathAnimation( camera_y );
	}
}

void Player::drawDeathAnimation( int camera_y ) {
	_death_anime_time++;
	int _angel_time = ( int )( _death_anime_time - FRAME * TIME_ANIMATION );
	int anim = 0;
	if ( _death_anime_time / ( int )( FRAME * TIME_ANIMATION ) > 0 ) {
		anim = 4;
		eraseUpBlock( );
		_erase_block = false;
	} else {
		anim = 3;
	}
	//酸欠
	double x1 = _x;
	double x2 = _x + DRAW_WIDTH;
	double y1 = _y - camera_y;
	double y2 =  y1 + DRAW_HEIGHT;

	if ( _air == CHECK_AIR ) {
		if ( _direct == DIR_LEFT ) {
			DrawRectExtendGraph( ( int )x1, ( int )y1, ( int )x2, ( int )y2, PLAYER_SIZE_X * anim, PLAYER_SIZE_Y * 1, PLAYER_SIZE_X, PLAYER_SIZE_Y, _img_handle, TRUE );
		} else {
			DrawRectExtendGraph( ( int )x1, ( int )y1, ( int )x2, ( int )y2, PLAYER_SIZE_X * anim, PLAYER_SIZE_Y * 0, PLAYER_SIZE_X, PLAYER_SIZE_Y, _img_handle, TRUE );
		}
	} else {
		//つぶれる
		DrawRectExtendGraph( ( int )x1, ( int )y1, ( int )x2, ( int )y2, PLAYER_SIZE_X * anim, PLAYER_SIZE_Y * 2, PLAYER_SIZE_X, PLAYER_SIZE_Y, _img_handle, TRUE );
	}
	//天使を描画
	if ( anim == 4 ) {
		double ANGEL_X = 50 * sin( _angel_time * 0.1 );
		int ANGEL_Y = -_angel_time * 3;
		DrawRectExtendGraph( _x + ( int )ANGEL_X, _y + ANGEL_Y, _x + DRAW_WIDTH + ( int )ANGEL_X, _y + DRAW_HEIGHT + ANGEL_Y, PLAYER_SIZE_X * ( _death_anime_time / 10 % 2 + 2 ), PLAYER_SIZE_Y * 6, PLAYER_SIZE_X, PLAYER_SIZE_Y, _img_handle, TRUE );
	}

	//復活
	if ( ( double )_angel_time / FRAME == REVIVE_TIME && _life > 0 ) {
		_life--;
		_air = 100;
		_death_anime_time = 0;
	}

}

bool Player::death( ) {
	if ( _air == CHECK_AIR ) {
		return true;
	}
	return false;
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

int Player::getY( ) {
	return _y;
}

bool Player::isStanding( ) const {
	return _standing;
}

void Player::move( ) {
	if ( CheckHitKey( KEY_INPUT_UP ) == 1 ) {
		_direct = DIR_UP;
	}
	if ( CheckHitKey( KEY_INPUT_DOWN ) == 1 ) {
		_direct = DIR_DOWN;
	}

	//移動キーチェック
	DIR move = DIR_NONE;
	if ( CheckHitKey( KEY_INPUT_LEFT ) == 1 ) {
		move = DIR_LEFT;
	}
	if ( CheckHitKey( KEY_INPUT_RIGHT ) == 1 ) {
		if ( move == DIR_LEFT ) {
			move = DIR_NONE;
		} else {
			move = DIR_RIGHT;
		}
	}

	if ( move != DIR_NONE ) {
		_direct = move;
		_move_anime_time++;
		//左:-1 右:1
		int dir = -1;
		if ( move == DIR_RIGHT || move == DIR_DOWN ) {
			dir = 1;
		}
		//移動ベクトル
		int vec_x = PLAYER_SPEED * dir;
		int vec_y = 0;
		//キャラクターのx:端y:中央 +vec
		int central_x = _x + ADJUST_X;
		int central_y = _y + ADJUST_Y;
		int check_x = central_x + CHARACTER_WIDTH / 2 * dir + vec_x;
		int check_y1 = central_y - CHARACTER_HEIGHT / 2;
		int check_y2 = central_y + CHARACTER_HEIGHT / 2 - 20;
		//ブロックが存在するかチェック
		std::shared_ptr< Block > block1 = _board->getBlock( check_x, check_y1 );
		std::shared_ptr< Block > block2 = _board->getBlock( check_x, check_y2 );
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
				vec_x = 0;
				//登れるかチェック
				_up++;
				if ( _up >= ( int )( FRAME * UP_TIME ) ) {
					std::shared_ptr< Block > slant_block = _board->getBlock(   check_x, central_y - BLOCK_HEIGHT );
					std::shared_ptr< Block > up_block    = _board->getBlock( central_x, central_y - BLOCK_HEIGHT );
					if ( ( !up_block    ||    up_block->getBlockID( ) == BLOCK_ID_AIR ) &&
						 ( !slant_block || slant_block->getBlockID( ) == BLOCK_ID_AIR ) ) {
						//登る
						vec_x += JUMP_X * dir;
						vec_y -= JUMP_Y;
					}
				}
			}
		} else {
			_up = 0;
		}
		//画面端
		if ( vec_x < 0 ) {
			if ( check_x + vec_x < 0 ) {
				vec_x = 0 - check_x;
			}
		}
		if ( vec_x > 0 ) {
			if ( check_x + vec_x > 900 ) {
				vec_x = 900 - check_x;
			}
		}
		//移動
		_x += vec_x;
		_y += vec_y;

	} else {
		//移動キーを押していない
		_move_anime_time = 0;
		_up = 0;
	}
}


void Player::fall( ) {
	int vec_y = PLAYER_SPEED;
	int check_x = _x + CHARACTER_WIDTH / 2 + 3;
	int check_y = _y + DRAW_HEIGHT - 20 + vec_y;

	//落下場所にブロックが存在しているかチェック
	std::shared_ptr< Block > block = _board->getBlock( check_x, check_y );
	if ( block ) {
		if ( block->getBlockID( ) != BLOCK_ID_AIR ) {
			_standing = true;
			vec_y = 0;
		}
	}

	//移動
	_y += vec_y;

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
	int check_x = 0;
	int check_y = 0;
	int central_x = _x + ADJUST_X;
	switch ( _direct ) {
	case DIR_UP:
		//上の位置
		check_x = central_x;
		check_y = _y - DRILL_RANGE;
		break;
	case DIR_DOWN:
		//下の位置
		check_x = central_x;
		check_y = _y + DRAW_HEIGHT + DRILL_RANGE;
		break;
	case DIR_LEFT:
		//左の位置
		check_x = central_x - CHARACTER_WIDTH / 2 - DRILL_RANGE;
		check_y = _y + ADJUST_Y;
		break;
	case DIR_RIGHT:
		//右の位置
		check_x = central_x + CHARACTER_WIDTH / 2 + DRILL_RANGE;
		check_y = _y + ADJUST_Y;
		break;
	}

	std::shared_ptr < Block > block = _board->getBlock( check_x, check_y );
	//ポインタが存在する場合true
	if ( block ) {
		if ( block->getBlockID( ) != BLOCK_ID_AIR ) {
			block->erase( );
		}
	}
}

void Player::ifAirRecover( ) {
	int check_x = _x + ADJUST_X;
	int check_y = _y + ADJUST_Y;
	std::shared_ptr < Block > block = _board->getBlock( check_x, check_y );
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
		int central_x = _x + ADJUST_X;
		int central_y = _y + ADJUST_Y;
		int check_x = 0;
		int check_y = 0;
		std::shared_ptr< Block > block = std::shared_ptr< Block >( );
		//中央列
		check_x = central_x ;
		check_y = central_y - BLOCK_HEIGHT * i;
		block = _board->getBlock( check_x, check_y );
		if ( block ) {
			if ( block->getBlockID( ) != BLOCK_ID_AIR ) {
				block->erase( );
			}
		}
		
		//左列
		check_x = central_x - BLOCK_WIDTH;
		check_y = central_y - BLOCK_HEIGHT * i;
		block = _board->getBlock( check_x, check_y );
		if ( block ) {
			if( block->getBlockID( ) != BLOCK_ID_AIR ) {
				block->erase( );
			}
		}

		//右列
		check_x = central_x + BLOCK_WIDTH;
		check_y = central_y - BLOCK_HEIGHT * i;
		block = _board->getBlock( check_x, check_y );
		if ( block ) {
			if( block->getBlockID( ) != BLOCK_ID_AIR ) {
				block->erase( );
			}
		}

	}
}
