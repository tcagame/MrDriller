#pragma once
#include "Block.h"
class BlockSolid  : public Block{
public:
	BlockSolid(  int x,int y );
	virtual ~BlockSolid( );
	void act( );
	int getBlockID( );
	void changeTxByConnect( ) { };
	void erase( );
private:
	int _hp;
};

