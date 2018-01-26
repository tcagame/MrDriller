#pragma once
#include <memory>
#include <list>
#include <array>
#include "Map.h"

class Board : public std::enable_shared_from_this< Board > {
public:
	Board( );
	virtual ~Board( );
public:
	void update( );
	void draw( int camera_y ) const;
public://get is
	std::shared_ptr< class Block > getBlockNow( int x, int y ) const;
	std::shared_ptr< class Block > getBlock( int x, int y ) const;
	std::shared_ptr< class Block > getBlockM( int mx, int my ) const;
	int getLevel( ) const;
	int getTopY( ) const;
	bool isFinished( ) const;
	bool isFireArea( int x, int y ) const;
public:
	void loadBlock( );
	void eraseBlock( std::shared_ptr< class Block > block );
	void eraseColumnBlockUp( int x, int y );
	void setCheck( bool check );
private:
	void updateBlocks( );
	void checkBlock( );
	void checkBlockPos( );
	void checkBlockConnect( );
	void checkBlockFall( );
	void checkBlockFallErase( );
private:
	int _top_y;
	bool _finished;
	bool _level_erase;
	int _level;
	bool _check;
	std::list< std::shared_ptr< class Block > > _blocks;
	std::array< std::shared_ptr< class Block >, BLOCK_WIDTH_NUM * BLOCK_HEIGHT_NUM > _virtual_blocks;
};