#include "BlockSolid.h"

const int INIT_HP = 5;

BlockSolid::BlockSolid( int x,int y ) :
Block ( x , y , 0, 16 * 20 ),
_hp( INIT_HP ) {
}


BlockSolid::~BlockSolid( )
{
}
void BlockSolid::act( ) {
	int tx = 16 * ( 16 - _hp );
	setTx( tx );
}

int BlockSolid::getBlockID( ){
	return BLOCK_ID_SOLID;
}

void BlockSolid::erase( bool destroy ) {
	_hp--;
	if ( _hp <= 0 || destroy ) {
		Block::erase( );
	}
}