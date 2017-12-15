#pragma once
#include "Block.h"
class BlockGreen : public Block {
public:
	BlockGreen( );
	virtual ~BlockGreen( );
public:
	int getBlockID( ) { return BLOCK_ID_GREEN; };
protected:
	void act( );//ŒÅ—Lˆ—
};

