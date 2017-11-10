#include "Player.h"
#include "DxLib.h"

//�萔�錾
const int TIME_AIR_DECREASE = 1;//AIR�̌��鑬�x
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

	//�L�[���͂�_x�𓮂���
	if ( CheckHitKey (KEY_INPUT_LEFT) == 1){
		_x -= PLAYER_SPEED * 1.0f;
	}
	if ( CheckHitKey (KEY_INPUT_RIGHT) == 1){
		_x += PLAYER_SPEED * 1.0f;
	}
}

void Player::draw( ) {
	//x0�Ay0, x1, y1, tx, ty, tw, th, handle, trans(����)
	//tx,ty�͉摜���̈ʒu�Btw,th�͕\���������摜���̃T�C�Y


	DrawRectExtendGraph( _x, _y, _x + CHARACTER_SIZE, _y + CHARACTER_SIZE, 0, 0, 25, 25, _img_handle, TRUE );
}


int Player::getAir( ) {
	return _air;
}