#include "BlockBlue.h"



BlockBlue::BlockBlue( int x, int y ) :
Block( x, y, 0, 0 ) {
}


BlockBlue::~BlockBlue( ) {
}

void BlockBlue::act( ) {
}

int BlockBlue::getBlockID( ) {
	return BLOCK_ID_BLUE;
}
