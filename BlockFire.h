#pragma once
#include "Block.h"
class BlockFire:public Block {
public:
	BlockFire( );
	virtual ~BlockFire( );
protected:
	void act( );//å≈óLèàóù
	int getBlockID( ) { return BLOCK_ID_FIRE; };
	void changeTxByConnect( ) { };
	void changeTy( ) { };
	void checkConnect( ) { };
private:
	int _count;
};

