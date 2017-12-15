#pragma once
#include "Block.h"
class BlockLevel : public Block {
public:
	BlockLevel( double x, double y );
	virtual ~BlockLevel( );
public:
	int getBlockID( ) { return BLOCK_ID_LEVEL; };
	void setFall( bool fall ) { };
protected:
	void act( );
};
