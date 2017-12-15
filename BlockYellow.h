#pragma once
#include "Block.h"

class BlockYellow : public Block {
public:
	BlockYellow( );
	virtual ~BlockYellow( );
protected:
	void act( );
	int getBlockID( ) { return BLOCK_ID_YELLOW; };
};

