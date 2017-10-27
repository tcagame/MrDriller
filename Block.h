#pragma once

//ブロック親クラス
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

//仮A
class BlueBlock : public Block {
public:
	BlueBlock( int x, int y ) :
		Block( x, y, 0, 0 ) {
	}
	~BlueBlock( ) { };
};

//仮B
class GreenBlock : public Block {
public:
	GreenBlock( int x, int y ) :
		Block( x, y, 0, 16 * 5 ) {
	}
	~GreenBlock( ) { };
};

class RedBlock : public Block {
public:
	RedBlock( int x, int y ) :
		Block( x, y, 0, 16 * 10 ) {
	}
	~RedBlock( ) { };
};

class YellowBlock : public Block {
public:
	YellowBlock( int x, int y ) :
		Block( x, y, 0, 16 * 15 ) {
	}
	~YellowBlock( ) { };
};