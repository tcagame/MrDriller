#include "Block.h"
#include "DxLib.h"
#include "Board.h"


const int SPRITE_SIZE = 16;
const double FALL_SPEED = 4;
const int MAX_ERASE_COUNT = 20;
const int ANIMATION_PATTERN = 6;
const int UPDATE_RANGE = BLOCK_HEIGHT * 13;
const int ERASE_RANGE = BLOCK_HEIGHT * 4;
const int CONNECT_RANGE = 4;
const int FALL_TIME = 60;

Block::Block( int tx, int ty ) :
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

void Block::init( double x, double y, std::shared_ptr< class Board > board ) {
	_x = x;
	_y = y;
	_board = board;
}


void Block::update( int camera_y ) {
	//処理
	act( );
	fall( );
	move( camera_y );
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

void Block::move( int camera_y ) {
	if ( !_fall ) {
		return;
	}
	
	{//移動先にブロックがないかチェック
		int mx = ( int )( _x + BLOCK_WIDTH / 2 ) / BLOCK_WIDTH;
		int my = ( int )( _y + _vec_y + 0.1 + BLOCK_HEIGHT ) / BLOCK_HEIGHT;

		std::shared_ptr< Block > other = _board->getBlockM( mx, my );
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

bool Block::isExistence( double x, double y ) const {
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
	
	//上下左右
	for ( int i = 0; i < MAX_DIR; i++ ) {
		if ( _connect_blocks[ i ] ) {
			int group = _connect_blocks[ i ]->getGroup( );
			if ( _group < group ) {
				_connect_blocks[ i ]->setGroup( _group );
			}
		}
	}
}

void Block::setFallGroup( bool fall ) {
	setFall( fall );
	
	//上下左右
	for ( int i = 0; i < MAX_DIR; i++ ) {
		if ( _connect_blocks[ i ] &&
			 _connect_blocks[ i ]->isFall( ) != _fall ) {
			_connect_blocks[ i ]->setFallGroup( _fall );
		}
	}
}


void Block::checkConnect( ) {
	//周りに同種類のブロックがないかチェックする
	double centra_x = _x + BLOCK_WIDTH / 2;
	double centra_y = _y + BLOCK_HEIGHT / 2;

	
	int mx = ( int )_x / BLOCK_WIDTH;
	int my = ( int )_y / BLOCK_HEIGHT;

	if ( !( _connect & CONNECT_UP ) ) {
		int check_mx = mx;
		int check_my = my - 1;
		std::shared_ptr< Block > block = _board->getBlockM( check_mx, check_my );
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
		std::shared_ptr< Block > block = _board->getBlockM( check_mx, check_my );
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
		std::shared_ptr< Block > block = _board->getBlockM( check_mx, check_my );
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
		std::shared_ptr< Block > block = _board->getBlockM( check_mx, check_my );
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
		int my = ( int )( _y + _vec_y ) / BLOCK_HEIGHT;
		_y = my * BLOCK_HEIGHT + 0.1;
		_vec_y = 0;
	}
}

void Block::resetConnect( ) {
	_connect = 0b00000000;
	for ( int i = 0; i < 4; i++ ) {
		_connect_blocks[ i ] = std::shared_ptr< Block >( );
	}
}
