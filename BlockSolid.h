#pragma once
#include "Block.h"
class BlockSolid  : public Block {
public:
	BlockSolid( );
	virtual ~BlockSolid( );
public:
	int getBlockID( ) { return BLOCK_ID_SOLID; };
	void act( );
	void changeTxByConnect( ) { };
	void changeTy( ) { };
	void erase( bool connect_erase = false, bool destroy = false );
private:
	int _hp;
};

