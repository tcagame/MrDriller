#pragma once
#include "Block.h"
class BlockAir:	public Block {
public:
	BlockAir( int x, int y );
	virtual ~BlockAir( );
protected:
	void act( );//ŒÅ—Lˆ—H

	int getBlockID();

private:
	int _count;
};

