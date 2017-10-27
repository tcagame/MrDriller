#include "Player.h"
#include "DxLib.h"

//定数宣言
const int TIME_AIR_DECREASE = 1;//AIRの減る速度


Player::Player( int x, int y ) :
_air( 100 ),
_count( 0 ) {
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
}

void Player::draw( ) {
	//x0、y0, x1, y1, tx, ty, tw, th, handle, trans(透過)
	//tx,tyは画像内の位置。tw,thは表示したい画像内のサイズ
	DrawRectExtendGraph(0, 0, 100, 100, 0, 0, 25, 25, _img_handle, TRUE);
}


int Player::getAir( ) {
	return _air;
}