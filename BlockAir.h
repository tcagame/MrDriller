#pragma once
#include "Block.h"
class BlockAir:	public Block {
public:
	BlockAir( double x, double y );
	virtual ~BlockAir( );
protected:
	void act( );//�ŗL�����H
	void eraseAnimation( );
	int getBlockID();
	void changeTxByConnect( ) { };
	void checkConnect( std::shared_ptr< class Board > board ) { };
private:
	int _count;
};

