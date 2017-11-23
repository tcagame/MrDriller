#pragma once
#include <memory>
#include <list>

class Board : public std::enable_shared_from_this< Board > {
public:
	Board( );
	virtual ~Board( );
public:
	void update( int camera_y );
	void draw( int camera_y ) const;
public:
	std::shared_ptr< class Block > getBlock( int x, int y ) const;
private:
	void load( );
private:
	int _img_handle;
	int _load_idx;
	std::list< std::shared_ptr< class Block > > _blocks;
};