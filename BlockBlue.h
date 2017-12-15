#pragma once
#include "Block.h"
class BlockBlue : public Block {
public:
	BlockBlue( );
	virtual ~BlockBlue( );
protected:
	void act( );//ŒÅ—Lˆ—
	int getBlockID( ) { return BLOCK_ID_BLUE; };
};

