#pragma once
#include "Block.h"
class BlockFire:public Block {
public:
	BlockFire( );
	virtual ~BlockFire( );
protected:
	void act( );//�ŗL����
	int getBlockID( ) { return BLOCK_ID_FIRE; };
	void changeTxByConnect( ) { };
	void checkConnect( bool erase = false ) { };
private:
	int _count;
};

