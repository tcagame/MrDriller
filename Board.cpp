#include "Board.h"
#include "DxLib.h"
#include "Block.h"
#include "BlockBlue.h"
#include "BlockGreen.h"
#include "BlockRed.h"
#include "BlockYellow.h"
#include "BlockAir.h"
#include "BlockLevel.h"
#include "BlockSolid.h"
#include "BlockFire.h"
#include "BlockIron.h"
#include "BlockBalloon.h"
#include "Camera.h"
#include "Map0.h"
#include "Map1.h"
#include "Map2.h"
#include "Map3.h"
#include "Map4.h"
#include <list>
#include <assert.h>

const int BLOCK_NUM = BLOCK_WIDTH_NUM * BLOCK_HEIGHT_NUM;
const int MAX_LEVEL = 5;

Board::Board( ) :
_level( 0 ),
_level_erase( true ),
_finished( false ),
_init_connect( true ) {
	_img_handle = LoadGraph( "Resource/Blocks.png", TRUE );
}

Board::~Board( ) {
	DeleteGraph( _img_handle );
}

void Board::update( ) {
	if ( _level_erase ) {
		if ( ( int )_blocks.size( ) == 0 ) {
			loadBlock( );
		}
	}
	checkBlockPos( );
	updateBlocks( );
}

void Board::draw( int camera_y ) const {
	for ( std::shared_ptr< Block > block : _blocks ) {
		block->draw( camera_y, _img_handle );
	}
	DrawFormatString( 0, 0, GetColor( 255, 255, 255 ), "Block:%d", ( int )_blocks.size( ) );
}

void Board::updateBlocks( ) {
	std::list< std::shared_ptr< Block > >::iterator ite = _blocks.begin( );
	while ( ite != _blocks.end( ) ) {
		std::shared_ptr< Block > block = *ite;
		block->update( );
		if ( block->isFinished( ) ) {
			ite = _blocks.erase( ite );
			continue;
		}
		ite++;
	}


}


void Board::loadBlock( ) {
	if ( MAX_LEVEL <= _level ) {
		_finished = true;
		return;
	}
	std::array< char, BLOCK_WIDTH_NUM * BLOCK_HEIGHT_NUM + 1 > map = { };

	srand( MAX_PATTERN );
	int pattern = rand( ) % MAX_PATTERN;
	
	switch ( _level ) {
	case 0:
		map = std::shared_ptr< Map >( new Map0 )->getMap( pattern );
		break;
	case 1:
		map = std::shared_ptr< Map >( new Map1 )->getMap( pattern );
		break;
	case 2:
		map = std::shared_ptr< Map >( new Map2 )->getMap( pattern );
		break;
	case 3:
		map = std::shared_ptr< Map >( new Map3 )->getMap( pattern );
		break;
	case 4:
		map = std::shared_ptr< Map >( new Map4 )->getMap( pattern );
		break;
	default:
		map = std::shared_ptr< Map >( new Map0 )->getMap( pattern );
		break;
	};
	
	for( int i = 0; i < BLOCK_WIDTH_NUM * BLOCK_HEIGHT_NUM; i++ ) {
		//処理が重いため保留
		std::shared_ptr< Block > block = std::shared_ptr< Block >( );
		switch ( map[ i ] ) {
		case 'R':
			block = std::shared_ptr< Block >( new BlockRed );
			break;
		case 'B':
			block = std::shared_ptr< Block >( new BlockBlue );
			break;
		case 'G':
			block = std::shared_ptr< Block >( new BlockGreen );
			break;
		case 'Y':
			block = std::shared_ptr< Block >( new BlockYellow );
			break;
		case 'A':
			block = std::shared_ptr< Block >( new BlockAir );
			break;
		case 'L':
			block = std::shared_ptr< Block >( new BlockLevel );
			break;
		case '*':
			block = std::shared_ptr< Block >( new BlockSolid );
			break;
		case 'F':
			block = std::shared_ptr< Block >( new BlockFire );
			break;
		case 'I':
			block = std::shared_ptr< Block >( new BlockIron );
			break;
		case 'O':
			block = std::shared_ptr< Block >( new BlockBalloon );
			break;
		}
		if ( !block ) {
			continue;
		}
		double x = ( i % BLOCK_WIDTH_NUM ) * BLOCK_WIDTH + 0.1;
		double y = ( i / BLOCK_WIDTH_NUM + _level * BLOCK_HEIGHT_NUM ) * BLOCK_HEIGHT + 0.1;
		block->init( x, y, shared_from_this( ) );
		_blocks.push_back( block );
	}
}

void Board::checkBlockPos( ) {
	std::array< std::shared_ptr< class Block >, BLOCK_NUM > tmp = { };
	
	for ( std::shared_ptr< Block > block : _blocks ) {
		int mx = ( int )block->getX( ) / BLOCK_WIDTH;
		int my = ( int )block->getY( ) / BLOCK_HEIGHT - _level * BLOCK_HEIGHT_NUM;
		int idx = my * BLOCK_WIDTH_NUM + mx;
		if ( idx < 0 || idx >= BLOCK_NUM ) {
			continue;
		}
		//assert( !tmp[ idx ] );
		tmp[ idx ] = block;
	}

	if ( _virtual_blocks != tmp ) {
		_virtual_blocks = tmp;
		checkConnect( );
		checkFall( );
	}
}

void Board::checkConnect( ) {
	std::shared_ptr< Board > this_ptr = shared_from_this( );
	for ( std::shared_ptr< Block > block : _blocks ) {
		block->resetConnect( );
	}
	for ( std::shared_ptr< Block > block : _blocks ) {
		block->checkConnect( );//!_init_connect
	}
	if ( _init_connect ) {
		_init_connect = false;
	}
}

int Board::getLevel( ) const {
	return _level;
}

std::shared_ptr< Block > Board::getBlockNow( double x, double y ) const {
	if ( x < 0 || y < 0 || x >= BLOCK_WIDTH_NUM * BLOCK_WIDTH ) {
		return std::shared_ptr< Block >( );
	}
	for ( std::shared_ptr< Block > block : _blocks ) {
		if ( block->isExistence( x, y ) ) {
			return block;
		}
	}
	return std::shared_ptr< Block >( );
}

std::shared_ptr< Block > Board::getBlock( double x, double y ) const {
	if ( x < 0 || y < 0 || x >= BLOCK_WIDTH_NUM * BLOCK_WIDTH ) {
		return std::shared_ptr< Block >( );
	}
	int mx = ( int )x / BLOCK_WIDTH;
	int my = ( int )y / BLOCK_HEIGHT;
	return getBlockM( mx, my );
}

std::shared_ptr< Block > Board::getBlockM( int mx, int my ) const {
	my -= _level * BLOCK_HEIGHT_NUM;
	if ( mx < 0 || mx >= BLOCK_WIDTH_NUM ||
		 my < 0 || my >= BLOCK_HEIGHT_NUM ) {
		return std::shared_ptr< Block >( );
	}

	int idx = my * BLOCK_WIDTH_NUM + mx;
	if ( idx >= BLOCK_WIDTH_NUM * BLOCK_HEIGHT_NUM ) {
		return std::shared_ptr< Block >( );
	}
	return _virtual_blocks[ idx ];
}

void Board::checkFall( ) {
	for ( std::shared_ptr< Block > block : _blocks ) {
		block->setFall( true );
	}

	for ( int i = 0; i < BLOCK_NUM; i++ ) {
		int idx = BLOCK_NUM - i - 1;
		if ( !_virtual_blocks[ idx ] ||
			  _virtual_blocks[ idx ]->getBlockID( ) == BLOCK_ID_LEVEL ) {
			continue;
		}
		if ( !_virtual_blocks[ idx ]->isFall( ) ) {
			continue;
		}
		int mx = ( idx % BLOCK_WIDTH_NUM );
		int my = ( idx / BLOCK_WIDTH_NUM );
		int check_idx = idx + BLOCK_WIDTH_NUM;
		//ブロックがない場合
		if ( !_virtual_blocks[ check_idx ] ) {
			_virtual_blocks[ idx ]->setFall( true );
			continue;
		}
		if ( _virtual_blocks[ check_idx ]->isFall( ) ) {
			_virtual_blocks[ idx ]->setFall( true );
			continue;
		}
		_virtual_blocks[ idx ]->setFallGroup( false );
	}
}


void Board::eraseBlock( std::shared_ptr< Block > block ) {
	block->erase( );
	if ( block->getBlockID( ) == BLOCK_ID_LEVEL ) {
		for ( std::shared_ptr< Block > block2 : _blocks ) {
			block2->erase( true );
		}
		_init_connect = true;
		_level_erase = true;
		_level++;
	}

}

int Board::getGroupBlockNum( int group ) const {
	int num = 0;
	for ( std::shared_ptr< Block > block : _blocks ) {
		if ( block->getGroup( ) == group ) {
			num++;
		}
	}
	return num;
}

void Board::eraseColumnBlockUp( double x, double y ) {
	if ( x < 0 || x > BLOCK_WIDTH * BLOCK_WIDTH_NUM ) {
		return;
	}
	y -= _level * BLOCK_HEIGHT_NUM * BLOCK_HEIGHT;
	int mx = ( int )x / BLOCK_WIDTH;
	int my = ( int )y / BLOCK_HEIGHT;
	for ( int i = 0; i <= my; i++ ) {
		int idx = i * BLOCK_WIDTH_NUM + mx;
		if ( !_virtual_blocks[ idx ] ) {
			continue;
		}
		if ( _virtual_blocks[ idx ]->getBlockID( ) != BLOCK_ID_AIR ) {
			_virtual_blocks[ idx ]->erase( true );
		}
	}
	checkConnect( );
}

bool Board::isFinished( ) const {
	return _finished;
}
