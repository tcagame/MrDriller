#include "Board.h"
#include "DxLib.h"
#include "BlockBlue.h"
#include "BlockGreen.h"
#include "BlockRed.h"
#include "BlockYellow.h"
#include "BlockAir.h"
#include "BlockLevel.h"
#include "BlockSolid.h"
#include "map.h"
#include <list>


const int BLOCK_WIDTH_NUM = 9;
const int BLOCK_WIDTH_SIZE = 100;
const int BLOCK_HEIGHT_SIZE = 60;


Board::Board( ) {
	_img_handle = LoadGraph( "Resource/Blocks.png", TRUE );
	for( int i = 0; i < MAP_WIDTH_NUM * MAP_HEIGHT_NUM; i++ ) {
		//ˆ—‚ªd‚¢‚½‚ß•Û—¯
		if ( i > 100 ) {
			break;
		}
		int x = ( i % BLOCK_WIDTH_NUM ) * BLOCK_WIDTH_SIZE;
		int y = ( i / BLOCK_WIDTH_NUM ) * BLOCK_HEIGHT_SIZE;
		switch ( MAP1[ i ] ) {
		case 'R':
			_blocks.push_back( std::shared_ptr< Block >( new BlockRed( x, y ) ) );
			break;
		case 'B':
			_blocks.push_back( std::shared_ptr< Block >( new BlockBlue( x,y ) ) );
			break;
		case 'G':
			_blocks.push_back( std::shared_ptr< Block >( new BlockGreen(x, y) ) );
			break;
		case 'Y':
			_blocks.push_back( std::shared_ptr< Block >( new BlockYellow(x,y) ) );
			break;
		case 'A':
			_blocks.push_back( std::shared_ptr< Block >( new BlockAir( x,y ) ) );
			break;
		case 'L':
			_blocks.push_back( std::shared_ptr< Block >( new BlockLevel( x,y) ) );
			break;
		case '*':
			_blocks.push_back( std::shared_ptr< Block >( new BlockSolid( x,y) ) );
			break;
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

void Board::draw( int camera_y ) const {
	for ( std::shared_ptr< Block > block : _blocks ) {
		block->draw( camera_y, _img_handle );
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
