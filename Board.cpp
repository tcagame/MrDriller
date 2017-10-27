#include "Board.h"
#include "DxLib.h"
#include "Block.h"
#include <list>


const int BLOCK_WIDTH_NUM = 9;
const int BLOCK_WIDTH_SIZE = 100;
const int BLOCK_HEIGHT_SIZE = 60;
const int KIND_OF_BLOCK = 4;


Board::Board( ) {
	_img_handle = LoadGraph( "Resource/Blocks.png", TRUE );
	for ( int i = 0; i < 100; i++ ) {
		int x = ( i % BLOCK_WIDTH_NUM ) * BLOCK_WIDTH_SIZE;
		int y = ( i / BLOCK_WIDTH_NUM ) * BLOCK_HEIGHT_SIZE;
		if ( i % KIND_OF_BLOCK == 0 ) {
			_blocks.push_back( std::shared_ptr< Block >( new BlueBlock( x, y ) ) ); 
		} else if ( i % KIND_OF_BLOCK == 1 ) {
			_blocks.push_back( std::shared_ptr< Block >( new GreenBlock( x, y ) ) );
		} else if ( i % KIND_OF_BLOCK == 2 ) {
			_blocks.push_back( std::shared_ptr< Block >( new RedBlock( x, y ) ) );
		} else if ( i % KIND_OF_BLOCK == 3 ) {
			_blocks.push_back( std::shared_ptr< Block >( new YellowBlock( x, y ) ) );
		}
	}
}

Board::~Board( ) {
	DeleteGraph( _img_handle );
}

void Board::update( ) {
	std::list< std::shared_ptr< Block > >::iterator ite = _blocks.begin( );
	while ( ite != _blocks.end( ) ) {
		updateBlock( *ite );
		ite++;
	}
}

void Board::draw( ) {
	//x0、y0, x1, y1, tx, ty, tw, th, handle, trans(透過)
	//tx,tyは画像内の位置。tw,thは表示したい画像内のサイズ
	std::list< std::shared_ptr< Block > >::iterator ite = _blocks.begin( );

	while ( ite != _blocks.end( ) ) {
	 	std::shared_ptr< Block > block = *ite;
		DrawRectExtendGraph( ( int )block->x, ( int )block->y, ( int )block->x + BLOCK_WIDTH_SIZE, ( int )block->y + BLOCK_HEIGHT_SIZE, block->tx, block->ty, block->tw, block->th, _img_handle, TRUE );
		ite++;
	}
}