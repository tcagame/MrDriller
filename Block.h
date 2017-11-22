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
class Block {
public:
	Block( int x, int y, int tx, int ty );
	virtual ~Block( );
public:
	void update( std::shared_ptr< class Board > board );
	void draw( int camera_y, int img_handle ) const;
	bool isExistence( int x, int y ) const;
	bool isFinished( ) const;
	bool isErase( ) const;
	virtual void erase( );
	void checkConnect( std::shared_ptr< class Board > board );
	double getY( ) const;
	double getX( ) const;
	virtual int getBlockID( ) = 0;
	void adjustPos( std::shared_ptr< Board > board );
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
	void move( std::shared_ptr< Board > board );
	void checkErase( );
	bool isInCamera( int camera_y ) const;
private:
	double _x;
	double _y;
	double _vec_y;
	int _tx;
	int _ty;
	int _count_erase;
	bool _erase;
	bool _finished;
	char _connect;
	std::array< std::shared_ptr< class Block >, MAX_DIR > _connect_blocks;
};


