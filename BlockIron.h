#pragma once
#include "Block.h"

class BlockIron  : public Block {
public:
	BlockIron( );
	virtual ~BlockIron( );
public:
	int getBlockID( ) { return BLOCK_ID_IRON; };
	void act( );
	void changeTxByConnect( ) { };
	void changeTy( ) { };
	void erase( bool connect_erase, bool destroy );
private:
	int _dv;
};

