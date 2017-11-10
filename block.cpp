#include "Block.h"
#include "DxLib.h"

const int WIDTH = 100;
const int HEIGHT = 60;
const int SPRITE_SIZE = 16;
const double FALL_SPEED = 2;

Block::Block( int x, int y, int tx, int ty ) :
_x( x ),
_y( y ),
_tx( tx ),
_ty( ty ) {
}

Block::~Block( ) {
}

void Block::update( ) {
	//�����ɗ��������Ȃǂ�����
	act( );
	fall( );
}

void Block::draw( int img_handle ) const {
	DrawRectExtendGraph( ( int )_x, ( int )_y, ( int )_x + WIDTH, ( int )_y + HEIGHT, _tx, _ty, SPRITE_SIZE, SPRITE_SIZE, img_handle, TRUE );
}

void Block::setTx( int tx ) {
	_tx = tx;
};

void Block::setTy( int ty ) {
	_ty = ty;
};

void Block::fall( ) {
	_y += FALL_SPEED;
}

bool Block::isExistence( int x, int y ) const {
	bool result = true;
	//��
	if ( x < _x ) {
		result = false;
	}
	//��
	if ( y < _y ) {
		result = false;
	}
	//�E
	if ( x > _x + WIDTH ) {
		result = false;
	}
	//��
	if ( y >  _y + HEIGHT ) {
		result = false;
	}
	return result;
}
