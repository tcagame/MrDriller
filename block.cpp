#include "Block.h"
#include "DxLib.h"

const int WIDTH = 100;
const int HEIGHT = 60;
const int SPRITE_SIZE = 16;

Block::Block( int x, int y, int tx, int ty ) :
_x( x ),
_y( y ),
_tx( tx ),
_ty( ty ) {
}

Block::~Block( ) {
}

void Block::update( ) {
	//Ç±Ç±Ç…óéâ∫èàóùÇ»Ç«ÇèëÇ≠
}

void Block::draw( int img_handle ) const {
	DrawRectExtendGraph( _x, _y, _x + WIDTH, _y + HEIGHT, _tx, _ty, SPRITE_SIZE, SPRITE_SIZE, img_handle, TRUE );
}

void Block::setTx( int tx ) {
	_tx = tx;
};

void Block::setTy( int ty ) {
	_ty = ty;
};
