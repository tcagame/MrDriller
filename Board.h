#pragma once
#include <memory>
#include <list>
#include <array>
#include "map.h"

class Board : public std::enable_shared_from_this< Board > {
public:
	Board( );
	virtual ~Board( );
public:
	void update( int camera_y );
	void draw( int camera_y ) const;
public:
	std::shared_ptr< class Block > getBlock( int x, int y ) const;
	std::shared_ptr< class Block > getBlockM( int x, int y ) const;
	void eraseBlock( std::shared_ptr< Block > block );
private:
	void loadBlock( );
	void updateBlocks( int camera_y );
	void checkBlockPos( );
	void checkConnect( );
	void checkFall( );
private:
	bool _level_erase;
	int _level;
	int _img_handle;
	std::list< std::shared_ptr< class Block > > _blocks;
	std::array< std::shared_ptr< class Block >, BLOCK_WIDTH_NUM * BLOCK_HEIGHT_NUM > _virtual_blocks;
};