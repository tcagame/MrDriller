#include "BlockGreen.h"



BlockGreen::BlockGreen( double x, double y ) :
Block( x, y, 0, 16 * 5 ) {
}


BlockGreen::~BlockGreen( ) {
}

void BlockGreen::act( ) {
}
int BlockGreen::getBlockID( ){
	return BLOCK_ID_GREEN;
}
