#include "Board.h"
#include "DxLib.h"
#include "Block.h"
#include <list>
#include <memory>


const int BLOCK_WIDTH_NUM = 9;
const int BLOCK_WIDTH_SIZE = 100;
const int BLOCK_HEIGHT_SIZE = 60;

static int g_img_handle = 0;
static std::list< std::shared_ptr< Block > > _blocks = { };

void initBoard( ) {
	g_img_handle = LoadGraph( "Resource/Blocks.png", TRUE );
	for ( int i = 0; i < 100; i++ ) {
		int x = ( i % BLOCK_WIDTH_NUM ) * BLOCK_WIDTH_SIZE;
		int y = ( i / BLOCK_WIDTH_NUM ) * BLOCK_HEIGHT_SIZE;
		if ( i % 2 == 0 ) {
			_blocks.push_back( std::shared_ptr< Block >( new BlockA( x, y ) ) ); 
		} else {
			_blocks.push_back( std::shared_ptr< Block >( new BlockB( x, y ) ) ); 
		}
	}
}

void updateBoard( ) {

}

void drawBoard( ) {
	//x0、y0, x1, y1, tx, ty, tw, th, handle, trans(透過)
	//tx,tyは画像内の位置。tw,thは表示したい画像内のサイズ
	std::list< std::shared_ptr< Block > >::iterator ite = _blocks.begin( );

while ( ite != _blocks.end( ) ) {
 	std::shared_ptr< Block > block = *ite;
	DrawRectExtendGraph( block->x, block->y, block->x + BLOCK_WIDTH_SIZE, block->y + BLOCK_HEIGHT_SIZE, block->tx, block->ty, block->tw, block->th, g_img_handle, TRUE );
	ite++;
}
	DrawRectExtendGraph( 0, 0, 100, 60, 0, 0, 16, 16, g_img_handle, TRUE);
}

void finalizeBoard( ) {
	DeleteGraph( g_img_handle );
}