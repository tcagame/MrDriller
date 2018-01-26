#pragma once
#include "Block.h"
class BlockBalloon : public Block {
public:
	BlockBalloon();
	virtual ~BlockBalloon();
public:
	int getBlockID( ) { return BLOCK_ID_BALLOON; };
	void setFall( bool fall ) { };
protected:
	void act( );
	void checkConnect( ){ };
	void fall( ){ };
};

