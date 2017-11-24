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
#include "map.h"
#include <list>

const int MAX_BLOCK = MAP_WIDTH_NUM * 18;
const int BLOCK_WIDTH_NUM = 9;

Board::Board( ) {
	_img_handle = LoadGraph( "Resource/Blocks.png", TRUE );
	_load_idx = 0;
	load( );
}

Board::~Board( ) {
	DeleteGraph( _img_handle );
}

void Board::update( int camera_y ) {
	load( );

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

	for ( std::shared_ptr< Block > block : _blocks ) {
		block->adjustPos( shared_from_this( ) );
	}
}

void Board::draw( int camera_y ) const {
	for ( std::shared_ptr< Block > block : _blocks ) {
		block->draw( camera_y, _img_handle );
	}
}

void Board::load( ) {
	for( ; _load_idx < MAP_WIDTH_NUM * MAP_HEIGHT_NUM; _load_idx++ ) {
		//ˆ—‚ªd‚¢‚½‚ß•Û—¯
		if ( _blocks.size( ) > MAX_BLOCK ) {
			break;
		}
		int x = ( _load_idx % BLOCK_WIDTH_NUM ) * BLOCK_WIDTH;
		int y = ( _load_idx / BLOCK_WIDTH_NUM ) * BLOCK_HEIGHT;
		switch ( MAP1[ _load_idx ] ) {
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


std::shared_ptr< Block > Board::getBlock( int x, int y ) const {
	if ( x < 0 || x > BLOCK_WIDTH_NUM * BLOCK_WIDTH ) {
		return std::shared_ptr< Block >( );
	}
	for ( std::shared_ptr< Block > block : _blocks ) {
		if ( block->isExistence( x, y ) ) {
			return block;
		}
	}
	return std::shared_ptr< Block >( );
}
