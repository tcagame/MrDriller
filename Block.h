#pragma once
#include <memory>

//�u���b�N�e�N���X
class Block {
public:
	Block( double x_, double y_, int tx_, int ty_ ) :
		x( x_),
		y( y_ ),
		tx( tx_ ),
		ty( ty_ ),
		tw( 16 ),
		th( 16 ) {
	};
	~Block( ) { };
public:
	double x;
	double y;
	double tx;
	double ty;
	double tw;
	double th;
};

//��A
class BlockA : public Block {
public:
	BlockA( int x, int y ) :
		Block( x, y, 0, 0 ) {
	}
	~BlockA( ) { };
};

//��B
class BlockB : public Block {
public:
	BlockB( int x, int y ) :
		Block( x, y, 0, 16 * 5 ) {
	}
	~BlockB( ) { };
};

void updateBlock( std::shared_ptr< Block > block );