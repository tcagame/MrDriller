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
#include "Camera.h"
#include <list>

const int BLOCK_NUM = BLOCK_WIDTH_NUM * BLOCK_HEIGHT_NUM;

Board::Board( ) {
	_img_handle = LoadGraph( "Resource/Blocks.png", TRUE );
	loadBlock( );
}

Board::~Board( ) {
	DeleteGraph( _img_handle );
}

void Board::update( int camera_y ) {
	checkBlockPos( );
	updateBlocks( camera_y );
}

void Board::draw( int camera_y ) const {
	for ( std::shared_ptr< Block > block : _blocks ) {
		block->draw( camera_y, _img_handle );
	}
	DrawFormatString( 0, 0, GetColor( 255, 255, 255 ), "Block:%d", ( int )_blocks.size( ) );
}

void Board::updateBlocks( int camera_y ) {
	std::list< std::shared_ptr< Block > >::iterator ite = _blocks.begin( );
	while ( ite != _blocks.end( ) ) {
		std::shared_ptr< Block > block = *ite;
		if ( block->isFinished( ) ) {
			ite = _blocks.erase( ite );
			continue;
		}

		block->update( shared_from_this( ), camera_y );
		ite++;
	}
}


void Board::loadBlock( ) {
	for( int i = 0; i < BLOCK_WIDTH_NUM * BLOCK_HEIGHT_NUM; i++ ) {
		//処理が重いため保留
		int x = ( i % BLOCK_WIDTH_NUM ) * BLOCK_WIDTH;
		int y = ( i / BLOCK_WIDTH_NUM ) * BLOCK_HEIGHT;
		switch ( MAP1[ i ] ) {
		case 'R':
			_blocks.push_back( std::shared_ptr< Block >( new BlockRed( x, y ) ) );
			break;
		case 'B':
			_blocks.push_back( std::shared_ptr< Block >( new BlockBlue( x, y ) ) );
			break;
		case 'G':
			_blocks.push_back( std::shared_ptr< Block >( new BlockGreen( x, y ) ) );
			break;
		case 'Y':
			_blocks.push_back( std::shared_ptr< Block >( new BlockYellow( x, y) ) );
			break;
		case 'A':
			_blocks.push_back( std::shared_ptr< Block >( new BlockAir( x, y ) ) );
			break;
		case 'L':
			_blocks.push_back( std::shared_ptr< Block >( new BlockLevel( x, y ) ) );
			break;
		case '*':
			_blocks.push_back( std::shared_ptr< Block >( new BlockSolid( x, y ) ) );
			break;
		}
	}
}

void Board::checkBlockPos( ) {
	std::array< std::shared_ptr< class Block >, BLOCK_NUM > tmp = { };
	
	for ( std::shared_ptr< Block > block : _blocks ) {
		int mx = ( int )( block->getX( ) + BLOCK_WIDTH / 2 ) / BLOCK_WIDTH;
		int my = ( int )( block->getY( ) + 0.1 ) / BLOCK_HEIGHT;
		int idx = my * BLOCK_WIDTH_NUM + mx;
		if ( idx < 0 || idx >= BLOCK_NUM ) {
			continue;
		}
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
		block->checkConnect( this_ptr );
	}
}




std::shared_ptr< Block > Board::getBlock( int x, int y ) const {
	if ( x < 0 || y < 0 || x >= BLOCK_WIDTH_NUM * BLOCK_WIDTH ) {
		return std::shared_ptr< Block >( );
	}
	int mx = x / BLOCK_WIDTH;
	int my = y / BLOCK_HEIGHT;
	int idx = my * BLOCK_WIDTH_NUM + mx;
	if ( idx >= BLOCK_WIDTH_NUM * BLOCK_HEIGHT_NUM ) {
		return std::shared_ptr< Block >( );
	}
	return _virtual_blocks[ idx ];
}

std::shared_ptr< Block > Board::getBlockM( int mx, int my ) const {
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
	for ( int i = 0; i < BLOCK_NUM; i++ ) {
		int idx = BLOCK_NUM - i - 1;
		if ( !_virtual_blocks[ idx ] ||
			  _virtual_blocks[ idx ]->getBlockID( ) == BLOCK_ID_LEVEL ) {
			continue;
		}
		int mx = ( idx % BLOCK_WIDTH_NUM );
		int my = ( idx / BLOCK_WIDTH_NUM );
		int check_idx = mx + ( my + 1 ) * BLOCK_WIDTH_NUM;
		//ブロックがない場合
		if ( !_virtual_blocks[ check_idx ] ) {
			_virtual_blocks[ idx ]->setFall( true );
			continue;
		}
		if ( _virtual_blocks[ check_idx ]->isFall( ) ) {
			_virtual_blocks[ idx ]->setFall( true );
		}
	}
	for ( std::shared_ptr< Block > block : _blocks ) {
		if ( !block->isFall( ) ) {
			block->setFallGroup( false );
		}
	}
}

void Board::eraseBlock( std::shared_ptr< Block > block ) {
	block->erase( );
	if ( block->getBlockID( ) != BLOCK_ID_SOLID ) {
		int group = block->getGroup( );
		for ( std::shared_ptr< Block > block2 : _blocks ) {
			if ( block2->getGroup( ) == group ) {
				block2->erase( );
			}
		}
	}
}

