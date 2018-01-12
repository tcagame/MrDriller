#include "BlockFire.h"


const int TY = 16 * 23;
const int WAIT_ANIM_TIME = 10;
const int MAX_ANIM_PATTERN = 5;
BlockFire::BlockFire( ) :
Block( 0, TY ),
_count( 0 ) {
}


BlockFire::~BlockFire( ) {
}

void BlockFire::act( ) {
	int tx = _count / WAIT_ANIM_TIME % MAX_ANIM_PATTERN * 16;
	setTx( tx );
	setTy( TY );
	_count++;
}
