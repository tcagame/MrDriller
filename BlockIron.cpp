#include "BlockIron.h"

const int INIT_DV = 5;

BlockIron::BlockIron( ) :
Block ( 16 * 21, 16 * 21 ),
_dv( INIT_DV ) {
}


BlockIron::~BlockIron( ){

}
void BlockIron::act( ) {
	
}

void BlockIron::erase( bool destroy ) {
	_dv--;
	if ( _dv <= 0 || destroy ) {
		Block::erase( );
	}
}