#include "Player.h"
#include "DxLib.h"

//�萔�錾
const int TIME_AIR_DECREASE = 1;//AIR�̌��鑬�x
const double TIME_ANIMATION = 0.5;
const int CHARACTER_SIZE = 100;
const int IMG_SIZE_X = 27;
const int IMG_SIZE_Y = 27;
const int PLAYER_SPEED = 4;


Player::Player( int x, int y ) :
_air( 100 ),
_count( 0 ),
_x( x ),
_y( y ),
_anime_time( 0 ) {
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
		_x -= PLAYER_SPEED;
	}
	if ( CheckHitKey (KEY_INPUT_RIGHT) == 1){
		_x += PLAYER_SPEED;
	}
}

void Player::draw( ) {
	//x0�Ay0, x1, y1, tx, ty, tw, th, handle, trans(����)
	//tx,ty�͉摜���̈ʒu�Btw,th�͕\���������摜���̃T�C�Y


	if ( !death( ) ) {
		DrawRectExtendGraph( _x, _y, _x + CHARACTER_SIZE, _y + CHARACTER_SIZE, 0, 0, 25, 25, _img_handle, TRUE );
	} else {
		drawDeathAnimation( );
	}
}

void Player::drawDeathAnimation( ) {
	//�_��
	_anime_time++;
	int anim = 0;
	if ( _anime_time / ( int )( 60 * TIME_ANIMATION ) > 0 ) {
		anim = 4;
	} else {
		anim = 3;
	}
	DrawRectExtendGraph( _x, _y, _x + CHARACTER_SIZE, _y + CHARACTER_SIZE, IMG_SIZE_X * anim, IMG_SIZE_Y * 0, IMG_SIZE_X, IMG_SIZE_Y, _img_handle, TRUE );
	//�Ԃ��
}

bool Player::death( ) {
	if ( _air <= 0 ) {
		return true;
	}
	return false;
}

int Player::getAir( ) {
	return _air;
}