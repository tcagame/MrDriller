#pragma once
#include "Block.h"
#include <list>

class Board {
public:
	Board( );
	virtual ~Board( );
public:
	void update( );
	void draw( );
private:
	int _img_handle;
	std::list< std::shared_ptr< Block > > _blocks;
};