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


//�u���b�N�e�N���X
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
	int getGroup( ) const;
	int getX( ) const;
	int getY( ) const;
	virtual int getBlockID( ) = 0;
	void setFallGroup( bool fall );
public:
	virtual void erase( bool destroy = false );
	virtual void checkConnect( );
	void connectBlock( std::shared_ptr< class Block > block, int connect );
	void setGroup( int group );
	virtual void setFall( bool fall );
	void resetConnect( );
protected:
	void setFinished( bool finish );
	virtual void changeTxByConnect( );
	virtual void eraseAnimation( );
	virtual void act( ) = 0;//�ŗL����
	virtual void fall( );//��������
protected:
	//set�n
	void setTx( int tx );//�摜�����W
	void setTy( int ty );//�摜�����W
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
	int _group;
	int _init_group;
	int _fall_count;
	std::shared_ptr< class Board > _board;
	std::array< std::shared_ptr< class Block >, MAX_DIR > _connect_blocks;
	std::shared_ptr< class Block > _under_block;
};


