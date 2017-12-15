#include "BlockRed.h"



BlockRed::BlockRed( double x, double y ) :
Block( x, y, 0, 16 * 10 ) {
}


BlockRed::~BlockRed( ) {
}

void BlockRed::act( ) {
}
int BlockRed::getBlockID( ){
	return BLOCK_ID_RED;
}