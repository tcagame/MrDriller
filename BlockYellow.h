#pragma once
#include "Block.h"

class BlockYellow : public Block {
public:
	BlockYellow( double x, double y );
	virtual ~BlockYellow( );
protected:
	void act( );
	int getBlockID( );
};

