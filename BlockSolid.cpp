#include "BlockSolid.h"

const int INIT_HP = 5;

BlockSolid::BlockSolid( int x,int y ) :
Block ( x , y , 16*12, 16*20 ),
_hp( INIT_HP ) {
}


BlockSolid::~BlockSolid( )
{
}
void BlockSolid::act( ) {
}

int BlockSolid::getBlockID( ){
	return BLOCK_ID_SOLID;
}

void BlockSolid::erase( ) {
	_hp--;
	if ( _hp <= 0 ) erase( );
}