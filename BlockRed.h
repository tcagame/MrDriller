#pragma once
#include "Block.h"
class BlockRed : public Block {
public:
	BlockRed( int x, int y );
	virtual ~BlockRed( );
protected:
	void act( );//�ŗL����
	int getBlockID( );
};


