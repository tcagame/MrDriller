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
#include "BlockBomb.h"
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
_check( true ),
_top_y( -1 ) {
}

Board::~Board( ) {
}

void Board::update( ) {
	if ( _level_erase ) {
		if ( ( int )_blocks.size( ) == 0 ) {
			loadBlock( );
		}
	}
	if ( _check ) {
		checkBlock( );
	}
	updateBlocks( );
}

void Board::draw( int camera_y ) const {
	for ( std::shared_ptr< Block > block : _blocks ) {
		block->draw( camera_y );
	}
}

void Board::updateBlocks( ) {
	std::list< std::shared_ptr< Block > >::iterator ite = _blocks.begin( );
	while ( ite != _blocks.end( ) ) {
		std::shared_ptr< Block > block = *ite;
		block->update( );
		if ( block->isFinished( ) ) {
			setCheck( true );
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

	int pattern = GetRand( MAX_PATTERN );
	
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
		case '#':
			block = std::shared_ptr< Block >( new BlockBomb );
			break;
		}
		if ( !block ) {
			continue;
		}
		int x = ( i % BLOCK_WIDTH_NUM ) * BLOCK_WIDTH;
		int y = ( i / BLOCK_WIDTH_NUM + _level * BLOCK_HEIGHT_NUM ) * BLOCK_HEIGHT;
		if ( _top_y < 0 ) {
			_top_y = y;
		}
		block->init( x, y, shared_from_this( ) );
		_blocks.push_back( block );
	}
	checkBlock( );
}

void Board::checkBlock( ) {
	checkBlockPos( );
	checkBlockConnect( );
	checkBlockFall( );
	checkBlockFallErase( );
	setCheck( false );
}
void Board::checkBlockPos( ) {
	_virtual_blocks = { };

	for ( std::shared_ptr< Block > block : _blocks ) {
		if ( block->isErase( ) ) {
			continue;
		}
		int mx = block->getX( ) / BLOCK_WIDTH;
		int my = block->getY( ) / BLOCK_HEIGHT - _level * BLOCK_HEIGHT_NUM;
		int idx = my * BLOCK_WIDTH_NUM + mx;
		if ( idx < 0 || idx >= BLOCK_NUM ) {
			continue;
		}
		//assert( !tmp[ idx ] );
		_virtual_blocks[ idx ] = block;
	}
}

void Board::checkBlockConnect( ) {
	std::shared_ptr< Board > this_ptr = shared_from_this( );
	for ( std::shared_ptr< Block > block : _blocks ) {
		block->resetConnect( );
	}
	for ( std::shared_ptr< Block > block : _blocks ) {
		block->checkConnect( );
	}
}

int Board::getLevel( ) const {
	return _level;
}

int Board::getTopY( ) const {
	return _top_y;
}


std::shared_ptr< Block > Board::getBlockNow( int x, int y ) const {
	if ( x < 0 || y < 0 || x >= BLOCK_WIDTH_NUM * BLOCK_WIDTH ) {
		return std::shared_ptr< Block >( );
	}
	for ( std::shared_ptr< Block > block : _blocks ) {
		if ( block->isErase( ) ) {
			continue;
		}
		if ( block->isExistence( x, y ) ) {
			return block;
		}
	}
	return std::shared_ptr< Block >( );
}

std::shared_ptr< Block > Board::getBlock( int x, int y ) const {
	if ( x < 0 || y < 0 || x >= BLOCK_WIDTH_NUM * BLOCK_WIDTH ) {
		return std::shared_ptr< Block >( );
	}
	int mx = x / BLOCK_WIDTH;
	int my = y / BLOCK_HEIGHT;
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

void Board::checkBlockFall( ) {
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
			int count1 = _virtual_blocks[ check_idx ]->getFallCount( );
			int count2 = _virtual_blocks[ idx       ]->getFallCount( );
			if ( count1 == count2 ) {
				_virtual_blocks[ idx ]->setFall( true );
				continue;
			}
		}
		_virtual_blocks[ idx ]->setFallGroup( false );
	}
}

void Board::checkBlockFallErase( ) {
	for ( std::shared_ptr< Block > block : _blocks ) {
		block->checkFallErase( );
	}
}

void Board::eraseBlock( std::shared_ptr< Block > block ) {
	block->erase( true, false );
	if ( block->getBlockID( ) == BLOCK_ID_LEVEL ) {
		for ( std::shared_ptr< Block > block2 : _blocks ) {
			block2->erase( true, true );
		}
		_level_erase = true;
		_level++;
	}
	setCheck( true );
}

void Board::eraseColumnBlockUp( int x, int y ) {
	if ( x < 0 || x > BLOCK_WIDTH * BLOCK_WIDTH_NUM ) {
		return;
	}
	y -= _level * BLOCK_HEIGHT_NUM * BLOCK_HEIGHT;
	int mx = x / BLOCK_WIDTH;
	int my = y / BLOCK_HEIGHT;
	for ( int i = 0; i <= my; i++ ) {
		int idx = i * BLOCK_WIDTH_NUM + mx;
		if ( !_virtual_blocks[ idx ] ) {
			continue;
		}
		if ( _virtual_blocks[ idx ]->getBlockID( ) != BLOCK_ID_AIR ) {
			_virtual_blocks[ idx ]->erase( false, true );
		}
	}
	setCheck( true );
}

void Board::setCheck( bool check ) {
	_check = check;
}


bool Board::isFinished( ) const {
	return _finished;
}

bool Board::isFireArea( int x, int y ) const {
	if ( x < 0 || x > BLOCK_WIDTH * BLOCK_WIDTH_NUM ) {
		return false;
	}
	y -= _level * BLOCK_HEIGHT_NUM * BLOCK_HEIGHT;
	int mx = x / BLOCK_WIDTH;
	int my = y / BLOCK_HEIGHT;

	const int OFFSET[ 8 ][ 2 ] = {
		{ -1, -1 },
		{  0, -1 },
		{  1, -1 },

		{ -1,  0 },
		{  1,  0 },

		{ -1,  1 },
		{  0,  1 },
		{  1,  1 },
	};
	for ( int i = 0; i < 8; i++ ) {
		int check_mx = mx + OFFSET[ i ][ 0 ];
		int check_my = my + OFFSET[ i ][ 1 ];
		//範囲外
		if ( check_mx < 0 || check_mx >= BLOCK_WIDTH_NUM || check_my < 0 ) {
			continue;
		}
		int idx = check_mx + check_my * BLOCK_WIDTH_NUM;
		//ブロック無し
		if ( _virtual_blocks[ idx ] == std::shared_ptr< Block >( ) ) {
			continue;
		}
		//Fireブロック
		if ( _virtual_blocks[ idx ]->getBlockID( ) == BLOCK_ID_FIRE ) {
			return true;
		}
	}
	return false;
}

