#pragma once
#include "Block.h"
class BlockGreen : public Block {
public:
	BlockGreen( int x, int y );
	virtual ~BlockGreen( );
protected:
	void act( );//�ŗL����
	int getBlockID( );
};

