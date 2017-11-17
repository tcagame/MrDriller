#pragma once
#include "Block.h"
class BlockLevel : public Block {
public:
	BlockLevel( int x, int y );
	virtual ~BlockLevel();
protected:
	void act( );
	void fall( std::shared_ptr< class Board > ) { };
	int getBlockID( );
	void changeTxByConnect( ) { };
};
