#include "Block.h"
#include "DxLib.h"
#include "Board.h"


const int SPRITE_SIZE = 16;
const double FALL_SPEED = 8;
const int MAX_ERASE_COUNT = 10;
const int ANIMATION_PATTERN = 6;
const int UPDATE_RANGE = BLOCK_HEIGHT * 13;
const int ERASE_RANGE = BLOCK_HEIGHT * 4;
const int CONNECT_RANGE = 4;
const int FALL_TIME = 30;



const std::array< int, MAX_DIR > OFFSET_Y = { -1, 1,  0, 0 };
const std::array< int, MAX_DIR > OFFSET_X = {  0, 0, -1, 1 };
const std::array< int, MAX_DIR > CONNECT_OWN    = { CONNECT_UP  , CONNECT_DOWN, CONNECT_LEFT , CONNECT_RIGHT };
const std::array< int, MAX_DIR > CONNECT_OTHER  = { CONNECT_DOWN, CONNECT_UP  , CONNECT_RIGHT, CONNECT_LEFT  };

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
	_init_group = _group;
	group++;
}

Block::~Block( ) {
}

void Block::init( double x, double y, std::shared_ptr< class Board > board ) {
	_x = x;
	_y = y;
	_board = board;
}


void Block::update( ) {
	//処理
	act( );
	fall( );
	move( );
	changeTxByConnect( );
	eraseAnimation( );
}

void Block::draw( int camera_y, int img_handle ) const {
	if ( !isInCamera( camera_y ) ) {
		return;
	}
	double x1 = _x;
	if ( _fall_count < FALL_TIME * 0.8 ) {
		x1 = _x + sin( _fall_count * 0.8 ) * 2;
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
	_vec_y = 0;
	//落下しない
	if ( !_fall ) {
		_fall_count = 0;
		return;
	}
	//落下待機
	_fall_count++;
	if ( _fall_count < FALL_TIME ) {
		return;
	}
	//落下ベクトル
	_vec_y = FALL_SPEED;
}

void Block::move( ) {
	if ( _vec_y == 0 ) {
		return;
	}
	
	{//移動先にブロックがないかチェック
		double check_x = _x + BLOCK_WIDTH / 2;
		double check_y = _y + BLOCK_HEIGHT + _vec_y;

		//std::shared_ptr< Block > other = _board->getBlockNow( check_x, check_y );
		if ( _under_block ) {
			//ベクトル調整
			_y = _under_block->getY( ) - BLOCK_HEIGHT;
			if ( !_under_block->isFall( ) ) {
				//落下終了
				setFallGroup( false );
			}
		}
	}
	//移動
	_y += _vec_y;
	
}

bool Block::isExistence( double x, double y ) const {
	bool result = true;
	//上
	if ( y < _y ) {
		result = false;
	}
	//下
	if ( y >= _y + BLOCK_HEIGHT ) {
		result = false;
	}
	//左
	if ( x < _x ) {
		result = false;
	}
	//右
	if ( x >= _x + BLOCK_WIDTH ) {
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
	if ( destroy ) {
		return;
	}
	for ( int i = 0; i < MAX_DIR; i++ ) {
		if ( _connect_blocks[ i ] &&
			!_connect_blocks[ i ]->isErase( ) &&
			_connect_blocks[ i ]->getBlockID( ) != BLOCK_ID_SOLID ) {
			_connect_blocks[ i ]->erase( );
		}
	}
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
			if ( _group > group ) {
				setGroup( group );
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


void Block::checkConnect( bool erase ) {
	//周りに同種類のブロックがないかチェックする

	int mx = ( int )_x / BLOCK_WIDTH;
	int my = ( int )_y / BLOCK_HEIGHT;
	//上下左右
	for ( int i = 0; i < MAX_DIR; i++ ) {
		if ( _connect_blocks[ i ] ) {
			continue;
		}
		//周りの座標のブロックを取得
		int check_mx = mx + OFFSET_X[ i ];
		int check_my = my + OFFSET_Y[ i ];
		std::shared_ptr< Block > block = _board->getBlockM( check_mx, check_my );
		//ブロックが無い場合スルー
		if ( !block ) {
			continue;
		}
		//下のブロックは登録しておく
		if ( i == DIR_DOWN ) {
			_under_block = block;
		}
		//同じ種類のブロックではない場合はスルー
		if ( block->getBlockID( ) != getBlockID( ) ) {
			continue;
		}
		//接続
		connectBlock( block, CONNECT_OWN[ i ] );
		block->connectBlock( shared_from_this( ), CONNECT_OTHER[ i ] );
		//グループ化
		if ( block->getGroup( ) > getGroup( ) ) {
			block->setGroup( getGroup( ) );
		}
		if ( block->getGroup( ) < getGroup( ) ) {
			setGroup( block->getGroup( ) );
		}
		if ( erase ) {
			if ( _board->getGroupBlockNum( getGroup( ) ) > 4 ) {
				_board->eraseBlock( shared_from_this( ) );
			}
		}
		
	}
}

void Block::connectBlock( std::shared_ptr< class Block > block, int connect ) {
	std::array< int, MAX_DIR > connects = { CONNECT_UP, CONNECT_DOWN, CONNECT_LEFT, CONNECT_RIGHT };
	for ( int i = 0; i < MAX_DIR; i++ ) {
		if ( connect == connects[ i ] ) {
			_connect |= connects[ i ];
			_connect_blocks[ i ] = block;
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


void Block::setFall( bool fall ) {
	_fall = fall;
	if ( !_fall ) {
		int my = ( int )( _y + BLOCK_HEIGHT / 2 ) / BLOCK_HEIGHT;
		_y = my * BLOCK_HEIGHT + 0.1;
		_vec_y = 0;
	}
}

void Block::resetConnect( ) {
	_connect = 0b00000000;
	_connect_blocks = { };
	_under_block = std::shared_ptr< Block >( );
	_group = _init_group;
}
