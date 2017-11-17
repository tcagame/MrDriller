#include "BlockSolid.h"



BlockSolid::BlockSolid( int x,int y ) :
Block ( x , y , 16*12, 16*20 ) {
}


BlockSolid::~BlockSolid( )
{
}
void BlockSolid::act( ) {
}

int BlockSolid::getBlockID( ){
	return BLOCK_ID_SOLID;
}