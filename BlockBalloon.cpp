#include "BlockBalloon.h"
#include "Board.h"


BlockBalloon::BlockBalloon( ) :
Block( 0, 16 * 24 ) {
}


BlockBalloon::~BlockBalloon( ) {
}

void BlockBalloon::act( ) {

}

void BlockBalloon::erase( bool connect_erase, bool destroy ) {
	//周りのブロックを消す
	const int ERASE_BLOCK[ 8 ][ 2 ] {
		{  0 , -1 },//上
		{  0 ,  1 },//下
		{ -1 ,  0 },//左
		{  1 ,  0 },//右
		{ -1 , -1 },//左上
		{  1 , -1 },//右上
		{ -1 ,  1 },//左下
		{  1 ,  1 } //右下
	};

	std::shared_ptr< Board > board = getBoard( );

	int mx = getX( ) / BLOCK_WIDTH;
	int my = getY( ) / BLOCK_HEIGHT;

	Block::erase( false, destroy );

	for ( int i = 0; i < 8; i++ ) {
		int check_mx = mx - ERASE_BLOCK[ i ][ 0 ];
		int check_my = my - ERASE_BLOCK[ i ][ 1 ];
		std::shared_ptr< Block > block = board->getBlockM( check_mx, check_my );
		//blockがない場合抜ける
		if ( !block ) {
			continue;
		}
		//すでに消えている場合は
		if ( block->isErase( ) ) {
			continue;
		}
		//ブロックを消す
		block->erase( false, true );
	}

	//自分を削除
}