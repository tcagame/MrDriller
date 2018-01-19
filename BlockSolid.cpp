#include "BlockSolid.h"

const int INIT_HP = 5;

BlockSolid::BlockSolid( ) :
Block ( 0, 16 * 20 ),
_hp( INIT_HP ) {
}


BlockSolid::~BlockSolid( )
{
}
void BlockSolid::act( ) {
	int tx = 16 * ( 16 - _hp );
	setTx( tx );
}

void BlockSolid::erase( bool connect_erase, bool destroy ) {
	_hp--;
	if ( _hp <= 0 || destroy ) {
		Block::erase( connect_erase, destroy );
	}
}