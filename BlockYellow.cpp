#include "BlockYellow.h"



BlockYellow::BlockYellow( int x, int y ) :
Block( x, y, 0, 16 * 15 ) {
}


BlockYellow::~BlockYellow( ) {
}

void BlockYellow::act( ) {
}
int BlockYellow::getBlockID( ){
	return BLOCK_ID_YELLOW;
}
