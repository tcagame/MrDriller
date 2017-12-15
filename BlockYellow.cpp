#include "BlockYellow.h"



BlockYellow::BlockYellow( double x, double y ) :
Block( x, y, 0, 16 * 15 ) {
}


BlockYellow::~BlockYellow( ) {
}

void BlockYellow::act( ) {
}
int BlockYellow::getBlockID( ){
	return BLOCK_ID_YELLOW;
}
