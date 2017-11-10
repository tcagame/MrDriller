#pragma once
#include <memory>

const int BLOCK_WIDTH = 100;
const int BLOCK_HEIGHT = 60;

//ブロック親クラス
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
protected:
	virtual void act( ) = 0;//固有処理
protected:
	//set系
	void setTx( int tx );//画像内座標
	void setTy( int ty );//画像内座標
private:
	void fall( );//落下処理
private:
	double _x;
	double _y;
	int _tx;
	int _ty;
	bool _finished;
};


