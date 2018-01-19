#pragma once
#include <memory>
#include <array>
#include "BlockIDList.h"
#include "define.h"

const int BLOCK_WIDTH = 100;
const int BLOCK_HEIGHT = 60;
const int CONNECT_DOWN  = 0b0000001;
const int CONNECT_UP    = 0b0000010;
const int CONNECT_LEFT  = 0b0000100;
const int CONNECT_RIGHT = 0b0001000;


//ブロック親クラス
class Block : std::enable_shared_from_this< Block > {
public:
	Block( int tx, int ty );
	virtual ~Block( );
public:
	void init( int x, int y, std::shared_ptr< class Board > board );
	void update( );
	void draw( int camera_y, int img_handle ) const;
public:
	bool isExistence( int x, int y ) const;
	bool isFinished( ) const;
	bool isErase( ) const;
	bool isFall( ) const;
	bool isNumCheck( ) const;
	int getGroup( ) const;
	int getX( ) const;
	int getY( ) const;
	virtual int getBlockID( ) = 0;
	void setFallGroup( bool fall );
	void checkGroupNum( int* num );
public:
	virtual void erase( bool connect_erase = false, bool destroy = false );
	virtual void checkConnect( );
	void connectBlock( std::shared_ptr< class Block > block, int connect );
	void setGroup( int group );
	virtual void setFall( bool fall );
	void resetConnect( );
protected:
	void setFinished( bool finish );
	virtual void changeTxByConnect( );
	virtual void eraseAnimation( );
	virtual void act( ) = 0;//固有処理
	virtual void fall( );//落下処理
protected:
	//set系
	void setTx( int tx );//画像内座標
	void setTy( int ty );//画像内座標
private:
	void move( );
	bool isInCamera( int camera_y ) const;
private:
	int _x;
	int _y;
	int _vec_y;
	int _tx;
	int _ty;
	int _count_erase;
	char _connect;
	bool _erase;
	bool _finished;
	bool _fall;
	bool _falled;
	bool _num_check;
	int _group;
	int _group_num;
	int _init_group;
	int _fall_count;
	std::shared_ptr< class Board > _board;
	std::array< std::shared_ptr< class Block >, MAX_DIR > _connect_blocks;
	std::shared_ptr< class Block > _under_block;
};


