#pragma once
#include "Block.h"
class BlockBlue : public Block {
public:
	BlockBlue( );
	virtual ~BlockBlue( );
protected:
	void act( );//�ŗL����
	int getBlockID( ) { return BLOCK_ID_BLUE; };
};

