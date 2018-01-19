#pragma once
#include "Block.h"
class BlockFire:public Block {
public:
	BlockFire( );
	virtual ~BlockFire( );
protected:
	void act( );//ŒÅ—Lˆ—
	int getBlockID( ) { return BLOCK_ID_FIRE; };
	void changeTxByConnect( ) { };
	void checkConnect( ) { };
private:
	int _count;
};

