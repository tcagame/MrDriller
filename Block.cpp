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
_vec_y( 0 ),
_connect( 0 ),
_count_erase( 0 ),
_erase( false ),
_finished( false ) {
}

Block::~Block( ) {
}

void Block::update( std::shared_ptr< Board > board ) {
	//処理
	act( );
	fall( );
	move( board );
	checkErase( );
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

void Block::adjustPos( std::shared_ptr< Board > board ) {
	//連結しているブロックとの位置調整
	//上のブロックから順に処理されるとする


	//上
	if ( _connect_blocks[ DIR_UP ] ) {
		//ブロックが落ちてこない場合
		//ブロックに合わせる
		double up_y = _connect_blocks[ DIR_UP ]->getY( );
		if ( _y - up_y > BLOCK_HEIGHT ) {
			_y = up_y + BLOCK_HEIGHT;
		}
	}

	//下
	//処理しない
	
	//左
	if ( _connect_blocks[ DIR_LEFT ] ) {
		//ブロックが落ちていない場合
		//ブロックに合わせる
		double left_y = _connect_blocks[ DIR_LEFT ]->getY( );
		if ( _y > left_y ) {
			_y = left_y;
		}
	}

	//右
	if ( _connect_blocks[ DIR_RIGHT ] ) {
		//左のブロックが落ちていない場合
		//左のブロックに合わせる
		double right_y = _connect_blocks[ DIR_RIGHT ]->getY( );
		if ( _y > right_y ) {
			_y = right_y;
		}
	}
}

void Block::move( std::shared_ptr< Board > board ) {
	{//移動先にブロックがないかチェック
		double check_x = _x + BLOCK_WIDTH / 2;
		double check_y = _y + BLOCK_HEIGHT + _vec_y;
		std::shared_ptr< Block > other = board->getBlock( ( int )check_x, ( int )check_y );

		if ( other ) {
			//ベクトル調整
			int target_y = ( int )( other->getY( ) - BLOCK_HEIGHT );
			_vec_y = target_y - _y;
		}
	}

	//移動
	_y += _vec_y;
}

void Block::fall( ) {
	_vec_y = FALL_SPEED;
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

double Block::getX( ) const {
	return _x;
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
				_connect_blocks[ DIR_UP ] = block;
			}
		}
	}
	if ( !( _connect & CONNECT_DOWN ) ) {
		std::shared_ptr< Block > block = board->getBlock( ( int )centra_x, ( int )centra_y + BLOCK_HEIGHT );
		if ( block ) {
			if ( block->getBlockID( ) == getBlockID( ) ) {
				_connect |= CONNECT_DOWN;
				_connect_blocks[ DIR_DOWN ] = block;
			}
		}
	}
	if ( !( _connect & CONNECT_LEFT ) ) {
		std::shared_ptr< Block > block = board->getBlock( ( int )centra_x - BLOCK_WIDTH, ( int )centra_y );
		if ( block ) {
			if ( block->getBlockID( ) == getBlockID( ) ) {
				_connect |= CONNECT_LEFT;
				_connect_blocks[ DIR_LEFT ] = block;
			}
		}
	}
	if ( !( _connect & CONNECT_RIGHT ) ) {
		std::shared_ptr< Block > block = board->getBlock( ( int )centra_x + BLOCK_WIDTH, ( int )centra_y );
		if ( block ) {
			if ( block->getBlockID( ) == getBlockID( ) ) {
				_connect |= CONNECT_RIGHT;
				_connect_blocks[ DIR_RIGHT ] = block;
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

void Block::checkErase( ) {
	if ( isErase( ) ) {
		return;
	}

	for ( std::shared_ptr< Block > block : _connect_blocks ) {
		if ( !block ) {
			continue;
		}
		if ( block->isErase( ) ) {
			erase( );
			break;
		}
	}
}