#pragma once
#include "Block.h"
class BlockRed : public Block {
public:
	BlockRed( );
	virtual ~BlockRed( );
public:
	int getBlockID( ) { return BLOCK_ID_RED; };
protected:
	void act( );//ŒÅ—Lˆ—
};


