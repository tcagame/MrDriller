#include "Player.h"
#include "DxLib.h"

//�萔�錾
const int TIME_AIR_DECREASE = 1;//AIR�̌��鑬�x
const int CHARACTER_SIZE = 100;
const int PLAYER_SIZE_X = 27;
const int PLAYER_SIZE_Y = 27;
const int PLAYER_SPEED = 4;
const int CHARACTER_WIDTH = 70;
const int BLOCK_DEPTH = 5;
const int MOVE_WAIT = 5;
const int MOVE_PATTERN = 4;
const int DRILL_RANGE = 7;
const double TIME_ANIMATION = 0.5;


Player::Player( int x, int y, std::shared_ptr< Board > board ) :
	_board( board ),
	_air( 100 ),
	_count( 0 ),
	_depth( 0 ),
	_x( x ),
	_y( y ),
	_death_anime_time( 0 ),
	_move_anime_time( 0 ),
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
	if ( CheckHitKey( KEY_INPUT_SPACE ) == 1 ) {
		dig( );
	}
	_depth = _y / BLOCK_HEIGHT * BLOCK_DEPTH;
}

void Player::draw( ) {
	//x0�Ay0, x1, y1, tx, ty, tw, th, handle, trans(����)
	//tx,ty�͉摜���̈ʒu�Btw,th�͕\���������摜���̃T�C�Y
	if ( !death( ) ) {
		if ( _direct == DIR_LEFT ) {
			DrawRectExtendGraph( _x, _y, _x + CHARACTER_SIZE, _y + CHARACTER_SIZE, PLAYER_SIZE_X * ( _move_anime_time / MOVE_WAIT % MOVE_PATTERN ), PLAYER_SIZE_Y * 5, PLAYER_SIZE_X, PLAYER_SIZE_Y, _img_handle, TRUE );
		} else if ( _direct == DIR_RIGHT ) {
			DrawRectExtendGraph( _x, _y, _x + CHARACTER_SIZE, _y + CHARACTER_SIZE, PLAYER_SIZE_X * ( _move_anime_time / MOVE_WAIT % MOVE_PATTERN ), PLAYER_SIZE_Y * 4, PLAYER_SIZE_X, PLAYER_SIZE_Y, _img_handle, TRUE );
		} else if ( _direct == DIR_UP ) {
			DrawRectExtendGraph( _x, _y, _x + CHARACTER_SIZE, _y + CHARACTER_SIZE, PLAYER_SIZE_X * 0, PLAYER_SIZE_Y * 3, PLAYER_SIZE_X, PLAYER_SIZE_Y, _img_handle, TRUE );
		} else if ( _direct == DIR_DOWN ) {
			DrawRectExtendGraph( _x, _y, _x + CHARACTER_SIZE, _y + CHARACTER_SIZE, PLAYER_SIZE_X * 0, PLAYER_SIZE_Y * 0, PLAYER_SIZE_X, PLAYER_SIZE_Y, _img_handle, TRUE );
		} 
	} else {
		drawDeathAnimation( );
	}
}

void Player::drawDeathAnimation( ) {
	//�_��
	_death_anime_time++;
	int anim = 0;
	if ( _death_anime_time / ( int )( 60 * TIME_ANIMATION ) > 0 ) {
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
	if ( _air <= 0 ) {
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
	int central_x = _x + CHARACTER_SIZE / 2 + 5;
	if ( CheckHitKey( KEY_INPUT_LEFT ) == 1 ) {
		int check_x = central_x - CHARACTER_WIDTH / 2;//�L�����N�^�[�̍��[���A�������ɑ������ʒu
		int check_y = _y + CHARACTER_SIZE / 2;//�L�����N�^�[�̍����̔����𑫂����ʒu(�^��)
		if ( !_board->isExistence( check_x, check_y ) ) {
			_x -= PLAYER_SPEED;
			_direct = DIR_LEFT;
			_move_anime_time++;
		}

	}
	if ( CheckHitKey( KEY_INPUT_RIGHT ) == 1 ) {
		int check_x = central_x + CHARACTER_WIDTH / 2;//�L�����N�^�[�̍��[+����+�����E�ɑ������ʒu
		int check_y = _y + CHARACTER_SIZE / 2;//�L�����N�^�[�̍����̔����𑫂����ʒu(�^��)
		if ( !_board->isExistence( check_x, check_y ) ) {
			_x += PLAYER_SPEED;
			_direct = DIR_RIGHT;
			_move_anime_time++;
		}
	}
	if ( CheckHitKey( KEY_INPUT_UP ) == 1 ) {
		_direct = DIR_UP;
	}
	if ( CheckHitKey( KEY_INPUT_DOWN ) == 1 ) {
		_direct = DIR_DOWN;
	}
	if ( !CheckHitKey( KEY_INPUT_LEFT ) && !CheckHitKey( KEY_INPUT_RIGHT ) ) _move_anime_time = 0;
}


void Player::fall( ) {
	if ( isStanding( ) ) {
		_y += PLAYER_SPEED;
	}
}

void Player::dig( ) {
	int check_x = 0;
	int check_y = 0;
	int central_x = _x + CHARACTER_SIZE / 2 + 5;
	switch ( _direct ) {
	case DIR_UP:
	//��̈ʒu
		check_x = central_x;
		check_y = _y - DRILL_RANGE;
		break;
	case DIR_DOWN:
	//���̈ʒu
		check_x = central_x;
		check_y = _y + CHARACTER_SIZE + DRILL_RANGE;
		break;
	case DIR_LEFT:
	//���̈ʒu
		check_x = central_x - CHARACTER_WIDTH / 2 - DRILL_RANGE;
		check_y = _y + CHARACTER_SIZE / 2;
		break;
	case DIR_RIGHT:
	//�E�̈ʒu
		check_x = central_x + CHARACTER_WIDTH / 2 + DRILL_RANGE;
		check_y = _y + CHARACTER_SIZE / 2;
		break;
	}

	std::shared_ptr < Block > block = _board -> getBlock( check_x, check_y );
	//�|�C���^�����݂���ꍇtrue
	if ( block ) {
		block->erase( );
	}
}
