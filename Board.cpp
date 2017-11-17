#include "Board.h"
#include "DxLib.h"
#include "BlockBlue.h"
#include "BlockGreen.h"
#include "BlockRed.h"
#include "BlockYellow.h"
#include "BlockAir.h"
#include "BlockLevel.h"
#include <list>


const int BLOCK_WIDTH_NUM = 9;
const int BLOCK_WIDTH_SIZE = 100;
const int BLOCK_HEIGHT_SIZE = 60;
const int KIND_OF_BLOCK = 2;


Board::Board( ) {
	_img_handle = LoadGraph( "Resource/Blocks.png", TRUE );
	for( int i = 0; i < 100; i++ ) {
		int x = ( i % BLOCK_WIDTH_NUM ) * BLOCK_WIDTH_SIZE;
		int y = ( i / BLOCK_WIDTH_NUM ) * BLOCK_HEIGHT_SIZE;
		if( y != 0 && y != BLOCK_HEIGHT_SIZE ) {
			if( i % KIND_OF_BLOCK == 0 ) {
				_blocks.push_back( std::shared_ptr< Block >( new BlockBlue( x, y ) ) );
			} else if( i % KIND_OF_BLOCK == 1 ) {
				_blocks.push_back( std::shared_ptr< Block >( new BlockLevel( x, y ) ) );
			}
		}
	}
}

Board::~Board( ) {
	DeleteGraph( _img_handle );
}

void Board::update( ) {
	std::list< std::shared_ptr< Block > >::iterator ite = _blocks.begin( );
	while ( ite != _blocks.end( ) ) {
		std::shared_ptr< Block > block = *ite;
		if ( block->isFinished( ) ) {
			ite = _blocks.erase( ite );
			continue;
		}

		block->update( shared_from_this( ) );
		ite++;
	}
}

void Board::draw( ) {
	for ( std::shared_ptr< Block > block : _blocks ) {
		block->draw( _img_handle );
	}
}

std::shared_ptr< Block > Board::getBlock( int x, int y ) const {
	for ( std::shared_ptr< Block > block : _blocks ) {
		if ( block->isExistence( x, y ) ) {
			return block;
		}
	}
	return std::shared_ptr< Block >( );
}
