#pragma once
#include "Block.h"
class BlockSolid  : public Block{
public:
	BlockSolid( double x, double y );
	virtual ~BlockSolid( );
	void act( );
	int getBlockID( );
	void changeTxByConnect( ) { };
	void erase( bool destroy = false );
private:
	int _hp;
};

