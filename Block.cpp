#include "Block.h"
#include "DxLib.h"
#include "Board.h"
#include "Graph.h"
#include "Sound.h"

const int SPRITE_SIZE = 16;
const int MAX_ERASE_COUNT = 10;
const int ANIMATION_PATTERN = 6;
const int UPDATE_RANGE = BLOCK_HEIGHT * 13;
const int ERASE_RANGE = BLOCK_HEIGHT * 4;
const int CONNECT_RANGE = 4;
const int ERASE_BLOCK_NUM = 4;



const std::array< int, MAX_DIR > OFFSET_Y = { -1, 1,  0, 0 };
const std::array< int, MAX_DIR > OFFSET_X = {  0, 0, -1, 1 };
const std::array< int, MAX_DIR > CONNECT_OWN    = { CONNECT_UP  , CONNECT_DOWN, CONNECT_LEFT , CONNECT_RIGHT };
const std::array< int, MAX_DIR > CONNECT_OTHER  = { CONNECT_DOWN, CONNECT_UP  , CONNECT_RIGHT, CONNECT_LEFT  };

Block::Block( int tx, int ty ) :
_tx( tx ),
_ty( ty ),
_connect( 0 ),
_count_erase( 0 ),
_fall_count( 0 ),
_fall( false ),
_falled( false ),
_erase( false ),
_check_groupnum( false ),
_finished( false ) {
	static int group = 0;
	_group = group;
	_init_group = _group;
	group++;
}

Block::~Block( ) {
}

void Block::init( int x, int y, std::shared_ptr< class Board > board ) {
	_x = x;
	_y = y;
	_board = board;
	changeTy( );
}

void Block::changeTy( ) {
	_ty += _board->getLevel( ) * 16;
}

void Block::update( ) {
	//処理
	_check_groupnum = false;
	act( );
	fall( );
	changeTxByConnect( );
	eraseAnimation( );
}

void Block::draw( int camera_y ) const {
	if ( !isInCamera( camera_y ) ) {
		return;
	}
	int x1 = _x + BOARD_INTERVAL;
	//落ちるときの揺れ
	if ( _fall_count < BLOCK_FALL_TIME * 0.8 ) {
		x1 += ( int )( sin( _fall_count ) * 2 );
	}
	int x2 = x1 + BLOCK_WIDTH;
	int y1 = _y - camera_y;
	int y2 =  y1 + BLOCK_HEIGHT;
	Graph::get( )->draw( Graph::GRAPH_PLAY_BLOCK, TRUE, x1, y1, x2, y2, _tx, _ty, SPRITE_SIZE, SPRITE_SIZE );
}

void Block::setTx( int tx ) {
	_tx = tx;
};

void Block::setTy( int ty ) {
	_ty = ty;
};

void Block::fall( ) {
	//落下しない
	if ( !_fall ) {
		_fall_count = 0;
		return;
	}
	//落下待機
	_fall_count++;
	if ( _fall_count < BLOCK_FALL_TIME ) {
		return;
	}
	//落下
	_falled = true;
	_y += BLOCK_FALL_SPEED;
	int fall_count = _fall_count - BLOCK_FALL_TIME + 1;
	if ( fall_count > 1 && fall_count % BLOCK_FALL_COUNT == 0 ) {
		_board->setCheck( true );
	}
}

void Block::checkFallErase( ) {
	if ( !_falled ) {
		return;
	}
	if ( _fall ) {
		return;
	}

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

bool Block::isExistence( int x, int y ) const {
	//上
	if ( y < _y ) {
		return false;
	}
	//下
	if ( y >= _y + BLOCK_HEIGHT ) {
		return false;
	}
	//左
	if ( x < _x ) {
		return false;
	}
	//右
	if ( x >= _x + BLOCK_WIDTH ) {
		return false;
	}
	return true;
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

bool Block::isCheckGroupNum( ) const {
	return _check_groupnum;
}

void Block::erase( bool connect_erase, bool destroy ) {
	_erase = true;
	if ( !connect_erase ) {
		return;
	}
	for ( int i = 0; i < MAX_DIR; i++ ) {
		if ( _connect_blocks[ i ] &&
			!_connect_blocks[ i ]->isErase( ) ) {
			if ( destroy || _connect_blocks[ i ]->getBlockID( ) != BLOCK_ID_SOLID ) {
				_connect_blocks[ i ]->erase( connect_erase, destroy );
			}
		}
	}
}

int Block::getX( ) const {
	return ( int )_x;
}

int Block::getY( ) const {
	return ( int )_y;
}

int Block::getFallCount( )const {
	return _fall_count;
}

int Block::getGroup( ) const {
	return _group;
}

std::shared_ptr< class Board > Block::getBoard( ) {
	return _board;
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
	if ( !fall && _falled && !isErase( ) ) {
		int group_num = checkGroupNum( 0 );
		if ( group_num >= ERASE_BLOCK_NUM ) {
			erase( true, true );
			Sound::get( )->play( Sound::SOUND_BLOCK_FALL_CRUSH );
			_falled = false;
		}
	}
	for ( int i = 0; i < MAX_DIR; i++ ) {
		if ( _connect_blocks[ i ] &&
			 _connect_blocks[ i ]->isFall( ) != _fall ) {
			_connect_blocks[ i ]->setFallGroup( _fall );
		}
	}
}

int Block::checkGroupNum( int num ) {
	_check_groupnum = true;
	num++;
	
	for ( int i = 0; i < MAX_DIR; i++ ) {
		if ( num >= ERASE_BLOCK_NUM ) {
			break;
		}
		if ( _connect_blocks[ i ] &&
			 !_connect_blocks[ i ]->isCheckGroupNum( ) ) {
			num = _connect_blocks[ i ]->checkGroupNum( num );
		}
	}
	return num;
}


void Block::checkConnect( ) {
	//周りに同種類のブロックがないかチェックする

	int mx = _x / BLOCK_WIDTH;
	int my = _y / BLOCK_HEIGHT;
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
		int my = ( _y + BLOCK_HEIGHT / 2 ) / BLOCK_HEIGHT;
		_y = my * BLOCK_HEIGHT;
	}
}

void Block::resetConnect( ) {
	_connect = 0b00000000;
	_connect_blocks = { };
	_under_block = std::shared_ptr< Block >( );
	_group = _init_group;
}
