#include "Player.h"
#include "DxLib.h"

//定数宣言
const int TIME_AIR_DECREASE = 1;//AIRの減る速度
const int CHARACTER_SIZE = 100;


Player::Player( int x, int y ) :
_air( 100 ),
_count( 0 ),
_x( x ),
_y( y ) {
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

	//キー入力で_xを動かす
	if ( CheckHitKey (KEY_INPUT_LEFT) == 1){
		_x -= PLAYER_SPEED * 1.0f;
	}
	if ( CheckHitKey (KEY_INPUT_RIGHT) == 1){
		_x += PLAYER_SPEED * 1.0f;
	}
}

void Player::draw( ) {
	//x0、y0, x1, y1, tx, ty, tw, th, handle, trans(透過)
	//tx,tyは画像内の位置。tw,thは表示したい画像内のサイズ


	DrawRectExtendGraph( _x, _y, _x + CHARACTER_SIZE, _y + CHARACTER_SIZE, 0, 0, 25, 25, _img_handle, TRUE );
}


int Player::getAir( ) {
	return _air;
}