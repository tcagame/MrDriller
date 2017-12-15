#pragma once
#include "Block.h"
class BlockAir:	public Block {
public:
	BlockAir( );
	virtual ~BlockAir( );
public:
	int getBlockID( ) { return BLOCK_ID_AIR; };
protected:
	void act( );//ŒÅ—Lˆ—H
	void eraseAnimation( );
	void changeTxByConnect( ) { };
	void checkConnect( std::shared_ptr< class Board > board ) { };
private:
	int _count;
};

