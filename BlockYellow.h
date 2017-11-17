#pragma once
#include "Block.h"

class BlockYellow : public Block {
public:
	BlockYellow( int x, int y );
	virtual ~BlockYellow( );
protected:
	void act( );
	int getBlockID( );
};

