#pragma once
#include "Block.h"
class BlockRed : public Block {
public:
	BlockRed( double x, double y );
	virtual ~BlockRed( );
protected:
	void act( );//�ŗL����
	int getBlockID( );
};


