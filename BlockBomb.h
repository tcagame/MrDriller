#pragma once
#include "Block.h"
class BlockBomb : public Block {
public:
	BlockBomb( );
	virtual ~BlockBomb( );
protected:
	void erase( bool connect_erase, bool destroy );
	void checkConnect( ) { };
	int getBlockID( ) { return BLOCK_ID_BOMB; };
	void act( ) { };
};