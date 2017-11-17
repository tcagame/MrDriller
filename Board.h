#pragma once
#include <memory>
#include "Block.h"
#include <list>

class Board : public std::enable_shared_from_this< Board > {
public:
	Board( );
	virtual ~Board( );
public:
	void update( );
	void draw( );
	bool isExistence( int x, int y ) const;
	std::shared_ptr< Block > getBlock( int x, int y ) const;
private:
	int _img_handle;
	std::list< std::shared_ptr< Block > > _blocks;
};