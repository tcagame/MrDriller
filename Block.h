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
	Block( int x, int y, int tx, int ty );
	virtual ~Block( );
public:
	void update( std::shared_ptr< class Board > board, int camera_y );
	void draw( int camera_y, int img_handle ) const;
public:
	bool isExistence( int x, int y ) const;
	bool isFinished( ) const;
	bool isErase( ) const;
	bool isFall( ) const;
	double getX( ) const;
	double getY( ) const;
	virtual int getBlockID( ) = 0;
public:
	virtual void erase( );
	void adjustPos( std::shared_ptr< class Board > board );
	void connectBlock( std::shared_ptr< class Block >, int connect );
	void setFall( bool value );
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
	virtual void checkConnect( std::shared_ptr< class Board > board );
private:
	void move( std::shared_ptr< class Board > board, int camera_y );
	void checkErase( int camera_y );
	bool isInCamera( int camera_y ) const;
private:
	double _x;
	double _y;
	double _vec_y;
	int _tx;
	int _ty;
	int _count_erase;
	char _connect;
	bool _erase;
	bool _finished;
	bool _fall;
	std::array< std::shared_ptr< class Block >, MAX_DIR > _connect_blocks;
};


