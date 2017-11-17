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

void Block::update( ) {
	//ここに落下処理などを書く
	act( );
	//fall( );
	eraseAnimation( );
}

void Block::draw( int img_handle ) const {
	DrawRectExtendGraph( ( int )_x, ( int )_y, ( int )_x + BLOCK_WIDTH, ( int )_y + BLOCK_HEIGHT, _tx, _ty, SPRITE_SIZE, SPRITE_SIZE, img_handle, TRUE );
}

void Block::setTx( int tx ) {
	_tx = tx;
};

void Block::setTy( int ty ) {
	_ty = ty;
};

void Block::fall( ) {
	_y += FALL_SPEED;
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

int Block::getBlockID( ) {
	return 0;
}

void Block::checkConnect( std::shared_ptr< Board > board ) {
	//周りに同種類のブロックがないかチェックする
	if ( !( _connect & CONNECT_UP ) ) {
		std::shared_ptr< Block > block = board->getBlock( ( int )_x, ( int )_y - BLOCK_HEIGHT );
		if ( block ) {
			if ( block->getBlockID( ) == getBlockID( ) ) {
				_connect |= CONNECT_UP;
			}
		}
	}
	if ( !( _connect & CONNECT_DWON ) ) {
	}
	if ( !( _connect & CONNECT_LEFT ) ) {
	}
	if ( !( _connect & CONNECT_RIGHT ) ) {
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
