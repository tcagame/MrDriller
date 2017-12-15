#include "BlockAir.h"


const int TY = 16 * 20;
const int WAIT_ANIM_TIME = 10;
const int MAX_ANIM_PATTERN = 4;


BlockAir::BlockAir( ) :
Block( 0, TY ),
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

void BlockAir::eraseAnimation( ) {
	if ( isErase( ) ) {	
		setFinished( true );
	}
}
