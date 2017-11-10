#include "Player.h"
#include "DxLib.h"

//�萔�錾
const int TIME_AIR_DECREASE = 1;//AIR�̌��鑬�x
const double TIME_ANIMATION = 0.5;
const int CHARACTER_SIZE = 100;
const int PLAYER_SIZE_X = 27;
const int PLAYER_SIZE_Y = 27;
const int PLAYER_SPEED = 4;
const int BLOCK_DEPTH = 5;


Player::Player( int x, int y, std::shared_ptr< Board > board ) :
_board( board ),
_air( 100 ),
_count( 0 ),
_depth( 0 ),
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
		//�L�[���͂�_x�𓮂���
		move( );
	}
	//�u���b�N�ɏ���Ă���ꍇ
	fall( );
	dig( );
	_depth = _y / BLOCK_HEIGHT * BLOCK_DEPTH;
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
	if ( _direct == DIR_LEFT ) {
		DrawRectExtendGraph( _x, _y, _x + CHARACTER_SIZE, _y + CHARACTER_SIZE, PLAYER_SIZE_X * anim, PLAYER_SIZE_Y * 1, PLAYER_SIZE_X, PLAYER_SIZE_Y, _img_handle, TRUE );
	} else if ( _direct == DIR_RIGHT ) {
		DrawRectExtendGraph( _x, _y, _x + CHARACTER_SIZE, _y + CHARACTER_SIZE, PLAYER_SIZE_X * anim, PLAYER_SIZE_Y * 0, PLAYER_SIZE_X, PLAYER_SIZE_Y, _img_handle, TRUE );
	}
	//�Ԃ��
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

int Player::getDepth( ) {
	return _depth;
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

void Player::dig( ) {
	int check_x = 0;
	int check_y = 0;
	switch ( _direct ) {
	case DIR_UP:
	//��̈ʒu
		check_x = _x + 0;
		check_y = _y + 0;
		break;
	case DIR_DOWN:
	//���̈ʒu
		check_x = _x + 0;
		check_y = _y + 0;
		break;
	case DIR_LEFT:
	//���̈ʒu
		check_x = _x + 0;
		check_y = _y + 0;
		break;
	case DIR_RIGHT:
	//�E�̈ʒu
		check_x = _x + 0;
		check_y = _y + 0;
		break;
	}

	std::shared_ptr < Block > block = _board -> getBlock( check_x, check_y );
	//�|�C���^�����݂���ꍇtrue
	if ( block ) {
		block->erase( );
	}
}