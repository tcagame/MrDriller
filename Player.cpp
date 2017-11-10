#include "Player.h"
#include "DxLib.h"

//定数宣言
const int TIME_AIR_DECREASE = 1;//AIRの減る速度
const double TIME_ANIMATION = 0.5;
const int CHARACTER_SIZE = 100;
const int IMG_SIZE_X = 27;
const int IMG_SIZE_Y = 27;
const int PLAYER_SPEED = 4;


Player::Player( int x, int y, std::shared_ptr< Board > board ) :
_board( board ),
_air( 100 ),
_count( 0 ),
_x( x ),
_y( y ),
_anime_time( 0 ),
_direct( DIR_RIGHT ),
_standing( true ) {
	_img_handle = LoadGraph( "Resource/Character.png", TRUE );
}

Player::~Player( ) {
	DeleteGraph( _img_handle );
}

void Player::update( ) {
	_count++;
	if ( _count % ( 60 * TIME_AIR_DECREASE ) == 0 ) {
		_air--;
	}

	if ( !death( ) ) {
		//キー入力で_xを動かす
		move( );
		//ブロックに乗っている場合
		fall( );
	}
	//キー入力で_xを動かす
	int check_x = 0;
	int check_y = 0;
	if ( _board->isExistence( check_x, check_y ) ) {
		//check_x, check_yの位置にブロックがある場合true
	}
	if ( CheckHitKey (KEY_INPUT_LEFT) == 1){
		_x -= PLAYER_SPEED;
	}
	if ( CheckHitKey (KEY_INPUT_RIGHT) == 1){
		_x += PLAYER_SPEED;
	}
}

void Player::draw( ) {
	//x0、y0, x1, y1, tx, ty, tw, th, handle, trans(透過)
	//tx,tyは画像内の位置。tw,thは表示したい画像内のサイズ
	if ( !death( ) ) {
		DrawRectExtendGraph( _x, _y, _x + CHARACTER_SIZE, _y + CHARACTER_SIZE, 0, 0, 25, 25, _img_handle, TRUE );
	} else {
		drawDeathAnimation( );
	}
}

void Player::drawDeathAnimation( ) {
	//酸欠
	_anime_time++;
	int anim = 0;
	if ( _anime_time / ( int )( 60 * TIME_ANIMATION ) > 0 ) {
		anim = 4;
	} else {
		anim = 3;
	}
	if ( _direct == DIR_LEFT ) {
		DrawRectExtendGraph( _x, _y, _x + CHARACTER_SIZE, _y + CHARACTER_SIZE, IMG_SIZE_X * anim, IMG_SIZE_Y * 1, IMG_SIZE_X, IMG_SIZE_Y, _img_handle, TRUE );
	} else if ( _direct == DIR_RIGHT ) {
		DrawRectExtendGraph( _x, _y, _x + CHARACTER_SIZE, _y + CHARACTER_SIZE, IMG_SIZE_X * anim, IMG_SIZE_Y * 0, IMG_SIZE_X, IMG_SIZE_Y, _img_handle, TRUE );
	}
	//つぶれる
}

bool Player::death( ) {
	if ( _air <= 99 ) {
		return true;
	}
	return false;
}

int Player::getAir( ) {
	return _air;
}


bool Player::isStanding( ) const {
	return _standing;
}

void Player::move( ) {
	if ( CheckHitKey( KEY_INPUT_LEFT ) == 1 ) {
		_x -= PLAYER_SPEED;
		_direct = DIR_LEFT;
	}
	if ( CheckHitKey( KEY_INPUT_RIGHT ) == 1 ) {
		_x += PLAYER_SPEED;
		_direct = DIR_RIGHT;
	}
}

void Player::fall( ) {
	if ( isStanding( ) ) {
		_y += PLAYER_SPEED;
	}
}