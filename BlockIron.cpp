#include "BlockIron.h"

const int INIT_DV = 5;

BlockIron::BlockIron( ) :
Block ( 0, 16 * 22 ),
_dv( INIT_DV ) {
}


BlockIron::~BlockIron( ){

}
void BlockIron::act( ) {
int tx = 16 * ( 5 - _dv );
	setTx( tx );
}

void BlockIron::erase( bool destroy ) {
	_dv--;
	if ( _dv <= 0 || destroy ) {
		Block::erase( );
	}
}