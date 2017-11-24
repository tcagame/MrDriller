#include "Player.h"
#include "DxLib.h"
#include "Block.h"
#include <math.h>

//-----------�萔�錾------------//
//���x���f�U�C���n
const int PLAYER_SPEED = 4;
const int TIME_AIR_DECREASE = 1;//AIR�̌��鑬�x
const int MOVE_WAIT = 5;
const int DRILL_RANGE = 7;
const int REVIVE_TIME = 3;
const int CHECK_AIR = 0;
const int JUMP_X = 50;
const int JUMP_Y = BLOCK_HEIGHT + 1;
const int AIR_RECOVERY_POINT = 20;
const double UP_TIME = 0.3;
const int BLOCK_POINT = 10;
const  int SOLID_AIR = 20;

//���̑�
const int AIR_MAX = 100;
const int MOVE_PATTERN = 8;
const int BLOCK_DEPTH = 5;
const int FRAME = 60;

//�`��n
const double TIME_ANIMATION = 2.0;
const int SPRITE_SIZE = 64;
const int DRAW_WIDTH = 100;
const int DRAW_HEIGHT = 90;
//���W�n
const int CENTRAL_X = DRAW_WIDTH / 2 + 5;
const int CENTRAL_Y = DRAW_HEIGHT / 2;
const int UP_Y = 13 * DRAW_HEIGHT / SPRITE_SIZE;
const int DOWN_Y = 55 * DRAW_HEIGHT / SPRITE_SIZE;
const int LEFT_X = 13 * DRAW_WIDTH / SPRITE_SIZE;
const int RIGHT_X = 50 * DRAW_WIDTH / SPRITE_SIZE;

//-----------�֐���`------------//

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

	fall( );    //����
	if ( !death( ) ) {
		if ( isStanding( ) ) {
			control( ); //����
		}
		move( );    //�ړ�
		ifAirRecover( ); //�G�A��
		scoreBlock( ); //�u���b�N�|�C���g
	} else {
		_erase_block = false;
	}

	//�u���b�N�ɏ���Ă��Ȃ��ꍇ

	//�[��
	checkDepth( );
	decreaseAir( );
	checkCrushed( );

}

void Player::draw( int camera_y ) {
	//x0�Ay0, x1, y1, tx, ty, tw, th, handle, trans(����)
	//tx,ty�͉摜���̈ʒu�Btw,th�͕\���������摜���̃T�C�Y
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
	//�����蔻��f�o�b�O�p
	int left  = ( int )_x + LEFT_X;
	int right = ( int )_x + RIGHT_X;
	int up    = ( int )_y - camera_y + UP_Y;
	int down  = ( int )_y - camera_y + DOWN_Y;
	unsigned int color = GetColor( 255, 0, 0 );
	DrawBox( left, up, right, down, color, FALSE );
#endif
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

	//�_��
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
		//�Ԃ��
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

	//�V�g��`��
	if ( anim == 7 ) {
		int ANGEL_X = ( int )( 50 * sin( _angel_time * 0.1 ) );
		int ANGEL_Y = -_angel_time * 3;
		DrawRectExtendGraph( x1 + ANGEL_X, y1 + ANGEL_Y, x2 + ANGEL_X, y2 + ANGEL_Y, SPRITE_SIZE * ( _death_anime_time / 10 % 4 ), SPRITE_SIZE * 0, SPRITE_SIZE, SPRITE_SIZE, _img_handle, TRUE );
	}

	//����
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
	dig( );//�@��
}


void Player::move( ) {
	_standing = false;
	if ( _vec_y > 0 ) {
		//���u���b�N�ɓ�����
		int check_left = ( int )_x + LEFT_X + 1;
		int check_right = ( int )_x + RIGHT_X - 1;
		int check_y = ( int )( _y + DOWN_Y + _vec_y );

		//�����ꏊ�Ƀu���b�N�����݂��Ă��邩�`�F�b�N
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
		//�ړ��L�[�������Ă��Ȃ�
		_move_anime_time = 0;
		_up = 0;
	}

	if ( _vec_x != 0 ) {
		_move_anime_time++;
		
		//�`�F�b�N���W
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

		//�L�����N�^�[��x:�[y:���� +vec
		//�u���b�N�����݂��邩�`�F�b�N
		std::shared_ptr< Block > block1 = _board->getBlock( check_x, up_y );
		std::shared_ptr< Block > block2 = _board->getBlock( check_x, down_y );
		if ( block1 || block2 ) {//�u���b�N�ɓ��������ꍇ
			std::shared_ptr< Block > col_block = block2;
			if ( !col_block ) {
				col_block = block1;
			}
			if ( col_block->getBlockID( ) == BLOCK_ID_AIR ) {
				//���̃u���b�N���G�A�[
				_up = 0;
			} else {
				//���̃u���b�N���ʏ�
				//�ړ����Ȃ�
				double target = 0;
				if ( left ) {
					target = col_block->getX( ) + BLOCK_WIDTH - LEFT_X;
				} else {
					target = col_block->getX( ) - RIGHT_X;
				}
				_vec_x = target - _x;
				//�o��邩�`�F�b�N
				_up++;
				if ( _up >= ( int )( FRAME * UP_TIME ) ) {
					std::shared_ptr< Block > slant_block = _board->getBlock( check_x, central_y - BLOCK_HEIGHT );
					std::shared_ptr< Block > up_block    = _board->getBlock( central_x, central_y - BLOCK_HEIGHT );
					if ( ( !up_block    ||    up_block->getBlockID( ) == BLOCK_ID_AIR ) &&
						 ( !slant_block || slant_block->getBlockID( ) == BLOCK_ID_AIR ) ) {
						//�o��
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
		//��ʒ[
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

	//�ړ�
	_x += _vec_x;
	_y += _vec_y;
}


void Player::fall( ) {
	_vec_y = PLAYER_SPEED;
}

void Player::dig( ) {
	if ( CheckHitKey( KEY_INPUT_SPACE ) == TRUE ) {
		if ( !_hitspace ) {
			//�A���͏o���Ȃ�
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
		//��̈ʒu
		check_x = _x + CENTRAL_X;
		check_y = _y + UP_Y - DRILL_RANGE;
		break;
	case DIR_DOWN:
		//���̈ʒu
		check_x = _x + CENTRAL_X;
		check_y = _y + DOWN_Y + DRILL_RANGE;
		break;
	case DIR_LEFT:
		//���̈ʒu
		check_x = _x + LEFT_X - DRILL_RANGE;
		check_y = _y + CENTRAL_Y;
		break;
	case DIR_RIGHT:
		//�E�̈ʒu
		check_x = _x + RIGHT_X + DRILL_RANGE;
		check_y = _y + CENTRAL_Y;
		break;
	}

	std::shared_ptr < Block > block = _board->getBlock( ( int )check_x, ( int )check_y );
	//�|�C���^�����݂���ꍇtrue
	if ( block && !block->isErase( ) ) {
		if ( block->getBlockID( ) != BLOCK_ID_AIR ) {
			block->erase( );
		}
		if ( block->isErase( ) ) {
			if ( block->getBlockID( ) == BLOCK_ID_SOLID ) {
				//AIR������
				_air -= SOLID_AIR;
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
	//�L�����N�^�[�̏�̃u���b�N������
	for ( int i = 0; i < 10; i++ ) {
		//3��
		double check_y = _y + CENTRAL_Y - BLOCK_HEIGHT * i;
		double central_x = _x + CENTRAL_X;
		{//������
			double check_x = central_x;
			std::shared_ptr< Block > block = _board->getBlock( ( int )check_x, ( int )check_y );
			if ( block ) {
				if ( block->getBlockID( ) != BLOCK_ID_AIR ) {
					block->erase( );
				}
			}
		}
		
		{//����
			double check_x = central_x - BLOCK_WIDTH;
			std::shared_ptr< Block > block = _board->getBlock( ( int )check_x, ( int )check_y );
			if ( block ) {
				if ( block->getBlockID( ) != BLOCK_ID_AIR ) {
					block->erase( );
				}
			}
		}
	
		{//�E��
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
	if ( _count % ( FRAME * TIME_AIR_DECREASE ) == 0 && _air > CHECK_AIR ) {
		_air--;
		if ( _air <= 0 ) {
			_dead = true;
		}
	}
}

void Player::checkCrushed( ) {
	//���̈ʒu�Ƀu���b�N���������Ă��邩�m���߂�
	double check_x = _x + CENTRAL_X;
	double check_y = _y + UP_Y;
	std::shared_ptr< Block > block = _board->getBlock( ( int )check_x, ( int )check_y );
	if ( block ) {
		if ( block->getBlockID( ) != BLOCK_ID_AIR ) {
			_dead = true;
		}
	}
}

void Player::checkDepth( ) {
	_depth = ( int )_y / BLOCK_HEIGHT * BLOCK_DEPTH + BLOCK_DEPTH - 20;
}

void Player::scoreBlock( ) {
	double check_x = _x + CENTRAL_X;
	double check_y = _y + CENTRAL_Y;
	std::shared_ptr < Block > block = _board->getBlock( ( int )check_x, ( int )check_y );
	if ( block ) {
		if ( block->getBlockID( )) {
			block->erase( );
			_score += BLOCK_POINT;
		}
	}
}