#pragma once
#include "Block.h"
class BlockAir:	public Block {
public:
	BlockAir( );
	virtual ~BlockAir( );
public:
	int getBlockID( ) { return BLOCK_ID_AIR; };
protected:
	void act( );
	void eraseAnimation( );
	void changeTxByConnect( ) { };
	void changeTy( ) { };
	void checkConnect( ) { };
private:
	int _count;
};

