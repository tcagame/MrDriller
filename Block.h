#pragma once
#include <memory>

//ブロック親クラス
class Block {
public:
	Block( int x, int y, int tx, int ty );
	virtual ~Block( );
public:
	void update( );
	void draw( int img_handle ) const;
protected:
	virtual void act( ) = 0;//固有処理
protected:
	//set系
	void setTx( int tx );//画像内座標
	void setTy( int ty );//画像内座標
private:
	double _x;
	double _y;
	int _tx;
	int _ty;
};


