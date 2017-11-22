#include "Block.h"
#include "DxLib.h"
#include "Board.h"


const int SPRITE_SIZE = 16;
const double FALL_SPEED = 2;
const int MAX_ERASE_COUNT = 20;
const int ANIMATION_PATTERN = 6;


Block::Block( int x, int y, int tx, int ty ) :
_x( x ),
_y( y ),
_tx( tx ),
_ty( ty ),
_connect( 0 ),
_count_erase( 0 ),
_erase( false ),
_finished( false ) {
}

Block::~Block( ) {
}

void Block::update( std::shared_ptr< Board > board ) {
	//ここに落下処理などを書く
	act( );
	fall( board );
	checkConnect( board );
	changeTxByConnect( );
	eraseAnimation( );
}

void Block::draw( int camera_y, int img_handle ) const {
	if ( !isInCamera( camera_y ) ) {
		return;
	}
	double x1 = _x;
	double x2 = _x + BLOCK_WIDTH;
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

void Block::fall( std::shared_ptr< Board > board ) {
	double vec = FALL_SPEED;
	double check_x = _x + BLOCK_WIDTH / 2;
	double check_y = _y + BLOCK_HEIGHT + vec;

	std::shared_ptr< Block > other = board->getBlock( ( int )check_x, ( int )check_y );
	if ( other ) {
		//下にブロックがある
		int target_y = ( int )( other->getY( ) - BLOCK_HEIGHT );
		vec = target_y - _y;
	}
	_y += vec;
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
	if ( x > _x + BLOCK_WIDTH ) {
		result = false;
	}
	//下
	if ( y >  _y + BLOCK_HEIGHT ) {
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

void Block::erase( ) {
	_erase = true;
}

double Block::getY( ) const {
	return _y;
}

void Block::checkConnect( std::shared_ptr< Board > board ) {
	//周りに同種類のブロックがないかチェックする
	double centra_x = _x + BLOCK_WIDTH / 2;
	double centra_y = _y + BLOCK_HEIGHT / 2;
	if ( !( _connect & CONNECT_UP ) ) {
		std::shared_ptr< Block > block = board->getBlock( ( int )centra_x, ( int )centra_y - BLOCK_HEIGHT );
		if ( block ) {
			if ( block->getBlockID( ) == getBlockID( ) ) {
				_connect |= CONNECT_UP;
			}
		}
	}
	if ( !( _connect & CONNECT_DOWN ) ) {
		std::shared_ptr< Block > block = board->getBlock( ( int )centra_x, ( int )centra_y + BLOCK_HEIGHT );
		if ( block ) {
			if ( block->getBlockID( ) == getBlockID( ) ) {
				_connect |= CONNECT_DOWN;
			}
		}
	}
	if ( !( _connect & CONNECT_LEFT ) ) {
		std::shared_ptr< Block > block = board->getBlock( ( int )centra_x - BLOCK_WIDTH, ( int )centra_y );
		if ( block ) {
			if ( block->getBlockID( ) == getBlockID( ) ) {
				_connect |= CONNECT_LEFT;
			}
		}
	}
	if ( !( _connect & CONNECT_RIGHT ) ) {
		std::shared_ptr< Block > block = board->getBlock( ( int )centra_x + BLOCK_WIDTH, ( int )centra_y );
		if ( block ) {
			if ( block->getBlockID( ) == getBlockID( ) ) {
				_connect |= CONNECT_RIGHT;
			}
		}
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
