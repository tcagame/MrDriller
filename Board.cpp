#include "Board.h"
#include "DxLib.h"
#include "BlockBlue.h"
#include "BlockGreen.h"
#include "BlockRed.h"
#include "BlockYellow.h"
#include "BlockAir.h"
#include <list>


const int BLOCK_WIDTH_NUM = 9;
const int BLOCK_WIDTH_SIZE = 100;
const int BLOCK_HEIGHT_SIZE = 60;
const int KIND_OF_BLOCK = 5;


Board::Board( ) {
	_img_handle = LoadGraph( "Resource/Blocks.png", TRUE );
	for ( int i = 0; i < 100; i++ ) {
		int x = ( i % BLOCK_WIDTH_NUM ) * BLOCK_WIDTH_SIZE;
		int y = ( i / BLOCK_WIDTH_NUM ) * BLOCK_HEIGHT_SIZE;
		if ( i % KIND_OF_BLOCK == 0 ) {
			_blocks.push_back( std::shared_ptr< Block >( new BlockBlue( x, y ) ) ); 
		} else if ( i % KIND_OF_BLOCK == 1 ) {
			_blocks.push_back( std::shared_ptr< Block >( new BlockGreen( x, y ) ) );
		} else if ( i % KIND_OF_BLOCK == 2 ) {
			_blocks.push_back( std::shared_ptr< Block >( new BlockRed( x, y ) ) );
		} else if ( i % KIND_OF_BLOCK == 3 ) {
			_blocks.push_back( std::shared_ptr< Block >( new BlockYellow( x, y ) ) );
		} else if ( i % KIND_OF_BLOCK == 4 ) {
			_blocks.push_back( std::shared_ptr< Block >( new BlockAir( x, y ) ) );
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
		block->update( );
		ite++;
	}
}

void Board::draw( ) {
	std::list< std::shared_ptr< Block > >::iterator ite = _blocks.begin( );
	while ( ite != _blocks.end( ) ) {
		std::shared_ptr< Block > block = *ite;
		block->draw( _img_handle );
		ite++;
	}
}