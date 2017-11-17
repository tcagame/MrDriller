#pragma once
#include <memory>
#include "BlockIDList.h"

const int BLOCK_WIDTH = 100;
const int BLOCK_HEIGHT = 60;
const int CONNECT_UP    = 0b0000001;
const int CONNECT_DOWN  = 0b0000010;
const int CONNECT_LEFT  = 0b0000100;
const int CONNECT_RIGHT = 0b0001000;


//�u���b�N�e�N���X
class Block {
public:
	Block( int x, int y, int tx, int ty );
	virtual ~Block( );
public:
	void update( );
	void draw( int img_handle ) const;
	bool isExistence( int x, int y ) const;
	bool isFinished( ) const;
	void erase( );
	void checkConnect( std::shared_ptr< class Board > board );
	virtual int getBlockID( );
protected:
	virtual void act( ) = 0;//�ŗL����
protected:
	//set�n
	void setTx( int tx );//�摜�����W
	void setTy( int ty );//�摜�����W
private:
	void fall( );//��������
private:
	double _x;
	double _y;
	int _tx;
	int _ty;
	bool _finished;
	char _connect;
};


