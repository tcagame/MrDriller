#include "Block.h"
#include "DxLib.h"
#include "Board.h"
#include <math.h>


const int SPRITE_SIZE = 16;
const double FALL_SPEED = 4;
const int MAX_ERASE_COUNT = 20;
const int ANIMATION_PATTERN = 6;
const int UPDATE_RANGE = BLOCK_HEIGHT * 13;
const int ERASE_RANGE = BLOCK_HEIGHT * 4;
const int CONNECT_RANGE = 4;
const int FALL_TIME = 60;

Block::Block( int x, int y, int tx, int ty ) :
_x( x ),
_y( y ),
_tx( tx ),
_ty( ty ),
_vec_y( 0 ),
_connect( 0 ),
_count_erase( 0 ),
_fall_count( 0 ),
_fall( false ),
_erase( false ),
_finished( false ) {
	static int group = 0;
	_group = group;
	group++;
}

Block::~Block( ) {
}

void Block::update( std::shared_ptr< Board > board, int camera_y ) {
	//処理
	act( );
	fall( );
	move( board, camera_y );
	changeTxByConnect( );
	eraseAnimation( );
}

void Block::draw( int camera_y, int img_handle ) const {
	if ( !isInCamera( camera_y ) ) {
		return;
	}
	double x1 = _x;
	if ( _fall_count < FALL_TIME * 0.8) {
		x1 = _x + sin( _fall_count ) * 2;
	}
	double x2 = x1 + BLOCK_WIDTH;
	double y1 = _y - camera_y;
	double y2 =  y1 + BLOCK_HEIGHT;
	DrawRectExtendGraph( ( int )x1, ( int )y1, ( int )x2, ( int )y2, _tx, _ty, SPRITE_SIZE, SPRITE_SIZE, img_handle, TRUE );
}

void Block::setTx( int tx ) {
	_tx = tx;
};

void Block::setTy( int ty ) {
	_ty = ty;
};


void Block::fall( ) {
	if ( !_fall ) {
		_fall_count = 0;
		_vec_y = 0;
		return;
	}
	_fall_count++;
	if ( _fall_count < FALL_TIME ) {
		_vec_y = 0;
		return;
	}
	_vec_y = FALL_SPEED;
}

void Block::move( std::shared_ptr< Board > board, int camera_y ) {
	if ( !_fall ) {
		return;
	}
	
	{//移動先にブロックがないかチェック
		int mx = ( int )( _x + BLOCK_WIDTH / 2 ) / BLOCK_WIDTH;
		int my = ( int )( _y + _vec_y + 0.1 + BLOCK_HEIGHT ) / BLOCK_HEIGHT;

		std::shared_ptr< Block > other = board->getBlockM( mx, my );
		if ( other && !other->isFall( ) ) {
			//ベクトル調整
			int target_y = ( int )( ( my - 1 ) * BLOCK_HEIGHT );
			_vec_y = target_y - _y;
			//落下終了
			setFallGroup( false );
		}
	}
	//移動
	_y += _vec_y;
	
}

bool Block::isExistence( int x, int y ) const {
	bool result = true;
	//左
	if ( x < _x ) {
		result = false;
	}
	//上
	if ( y < _y ) {
		result = false;
	}
	//右
	if ( x >= _x + BLOCK_WIDTH ) {
		result = false;
	}
	//下
	if ( y >= _y + BLOCK_HEIGHT ) {
		result = false;
	}
	return result;
}

bool Block::isFinished( ) const {
	return _finished;
}

bool Block::isErase( ) const {
	return _erase;
}

bool Block::isFall( ) const {
	return _fall;
}


void Block::erase( bool destroy ) {
	_erase = true;
}

double Block::getY( ) const {
	return _y;
}

double Block::getX( ) const {
	return _x;
}

int Block::getGroup( ) const {
	return _group;
}

void Block::setGroup( int group ) {
	_group = group;
	
	//上
	if ( _connect_blocks[ DIR_UP ] ) {
		int group = _connect_blocks[ DIR_UP ]->getGroup( );
		if ( _group < group ) {
			_connect_blocks[ DIR_UP ]->setGroup( _group );
		}
	}

	//下
	if ( _connect_blocks[ DIR_DOWN ] ) {
		int group = _connect_blocks[ DIR_DOWN ]->getGroup( );
		if ( _group < group ) {
			_connect_blocks[ DIR_DOWN ]->setGroup( _group );
		}
	}
	
	//左
	if ( _connect_blocks[ DIR_LEFT ] ) {
		int group = _connect_blocks[ DIR_LEFT ]->getGroup( );
		if ( _group < group ) {
			_connect_blocks[ DIR_LEFT ]->setGroup( _group );
		}
	}

	//右
	if ( _connect_blocks[ DIR_RIGHT ] ) {
		int group = _connect_blocks[ DIR_RIGHT ]->getGroup( );
		if ( _group < group ) {
			_connect_blocks[ DIR_RIGHT ]->setGroup( _group );
		}
	}
}

void Block::setFallGroup( bool fall ) {
	setFall( fall );
	
	//上
	if ( _connect_blocks[ DIR_UP ] &&
		 _connect_blocks[ DIR_UP ]->isFall( ) != _fall ) {
		_connect_blocks[ DIR_UP ]->setFallGroup( _fall );
	}

	//下
	if ( _connect_blocks[ DIR_DOWN ] &&
		 _connect_blocks[ DIR_DOWN ]->isFall( ) != _fall ) {
		_connect_blocks[ DIR_DOWN ]->setFallGroup( _fall );
	}
	
	//左
	if ( _connect_blocks[ DIR_LEFT ] &&
		 _connect_blocks[ DIR_LEFT ]->isFall( ) != _fall ) {
		_connect_blocks[ DIR_LEFT ]->setFallGroup( _fall );
	}

	//右
	if ( _connect_blocks[ DIR_RIGHT ] &&
		 _connect_blocks[ DIR_RIGHT ]->isFall( ) != _fall ) {
		_connect_blocks[ DIR_RIGHT ]->setFallGroup( _fall );
	}
}


void Block::checkConnect( std::shared_ptr< Board > board ) {
	//周りに同種類のブロックがないかチェックする
	double centra_x = _x + BLOCK_WIDTH / 2;
	double centra_y = _y + BLOCK_HEIGHT / 2;

	
	int mx = ( int )( _x + BLOCK_WIDTH / 2 ) / BLOCK_WIDTH;
	int my = ( int )( _y + 0.1 ) / BLOCK_HEIGHT;

	if ( !( _connect & CONNECT_UP ) ) {
		int check_mx = mx;
		int check_my = my - 1;
		std::shared_ptr< Block > block = board->getBlockM( check_mx, check_my );
		if ( block && block->getBlockID( ) == getBlockID( ) ) {
			connectBlock( block, CONNECT_UP );
			block->connectBlock( shared_from_this( ), CONNECT_DOWN );

			if ( block->getGroup( ) > getGroup( ) ) {
				block->setGroup( getGroup( ) );
			} else {
				setGroup( block->getGroup( ) );
			}
		}
	}
	if ( !( _connect & CONNECT_DOWN ) ) {
		int check_mx = mx;
		int check_my = my + 1;
		std::shared_ptr< Block > block = board->getBlockM( check_mx, check_my );
		if ( block && block->getBlockID( ) == getBlockID( ) ) {
			connectBlock( block, CONNECT_DOWN );
			block->connectBlock( shared_from_this( ), CONNECT_UP );

			if ( block->getGroup( ) > getGroup( ) ) {
				block->setGroup( getGroup( ) );
			} else {
				setGroup( block->getGroup( ) );
			}
		}
	}
	if ( !( _connect & CONNECT_LEFT ) ) {
		int check_mx = mx - 1;
		int check_my = my;
		std::shared_ptr< Block > block = board->getBlockM( check_mx, check_my );
		if ( block && block->getBlockID( ) == getBlockID( ) ) {
			connectBlock( block, CONNECT_LEFT );
			block->connectBlock( shared_from_this( ), CONNECT_RIGHT );
			
			if ( block->getGroup( ) > getGroup( ) ) {
				block->setGroup( getGroup( ) );
			} else {
				setGroup( block->getGroup( ) );
			}
		}
	}
	if ( !( _connect & CONNECT_RIGHT ) ) {
		int check_mx = mx + 1;
		int check_my = my;
		std::shared_ptr< Block > block = board->getBlockM( check_mx, check_my );
		if ( block && block->getBlockID( ) == getBlockID( ) ) {
			connectBlock( block, CONNECT_RIGHT );
			block->connectBlock( shared_from_this( ), CONNECT_LEFT );
				
			if ( block->getGroup( ) > getGroup( ) ) {
				block->setGroup( getGroup( ) );
			} else {
				setGroup( block->getGroup( ) );
			}
		}
	}
}

void Block::connectBlock( std::shared_ptr< class Block > block, int connect ) {
	if ( connect == CONNECT_UP ) {
		_connect |= connect;
		_connect_blocks[ DIR_UP ] = block;
	}
	if ( connect == CONNECT_DOWN ) {
		_connect |= connect;
		_connect_blocks[ DIR_DOWN ] = block;
	}
	if ( connect == CONNECT_LEFT ) {
		_connect |= connect;
		_connect_blocks[ DIR_LEFT ] = block;
	}
	if ( connect == CONNECT_RIGHT ) {
		_connect |= connect;
		_connect_blocks[ DIR_RIGHT ] = block;
	}
}


void Block::eraseAnimation( ) {
	if ( !_erase ) {
		_count_erase = 0;
		return;
	}
	_count_erase++;
	if ( _count_erase > MAX_ERASE_COUNT ) {
		_finished = true;
	}
	int cx = _count_erase * ANIMATION_PATTERN / MAX_ERASE_COUNT + 16;
	_tx = cx * SPRITE_SIZE;
}

void Block::setFinished( bool finish ) {
	_finished = finish;
}

void Block::changeTxByConnect( ) {
	_tx = _connect * SPRITE_SIZE;
}

bool Block::isInCamera( int camera_y ) const {
	if ( _y + BLOCK_HEIGHT < camera_y ) {
		return false;
	}
	if ( _y > camera_y + 720 ) {
		return false;
	}
	return true;
}


void Block::setFall( bool fall ) {
	_fall = fall;
	if ( !_fall ) {
		int my = ( int )( _y + _vec_y + 0.1 ) / BLOCK_HEIGHT;
		_y = my * BLOCK_HEIGHT;
		_vec_y = 0;
	}
}
