#pragma once
#include "Block.h"
class BlockBlue : public Block {
public:
	BlockBlue( double x, double y );
	virtual ~BlockBlue( );
protected:
	void act( );//�ŗL����
	int getBlockID( );
};

