#pragma once
#include "Block.h"
class BlockGreen : public Block {
public:
	BlockGreen( double x, double y );
	virtual ~BlockGreen( );
protected:
	void act( );//ŒÅ—Lˆ—
	int getBlockID( );
};

