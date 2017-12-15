#include "BlockAir.h"


const int TY = 16 * 20;
const int WAIT_ANIM_TIME = 10;
const int MAX_ANIM_PATTERN = 4;


BlockAir::BlockAir( double x, double y ) :
Block( x, y, 0, TY ),
_count( 0 ) {
}


BlockAir::~BlockAir( ) {
}

void BlockAir::act( ) {
	int tx = _count / WAIT_ANIM_TIME % MAX_ANIM_PATTERN * 16;
	setTx( tx );
	setTy( TY );
	_count++;
}

int BlockAir::getBlockID() {
	return BLOCK_ID_AIR;
}

void BlockAir::eraseAnimation( ) {
	if ( isErase( ) ) {	
		setFinished( true );
	}
}
