#pragma once
#include <memory>

//�u���b�N�e�N���X
class Block {
public:
	Block( int x, int y, int tx, int ty );
	virtual ~Block( );
public:
	void update( );
	void draw( int img_handle ) const;
protected:
	virtual void act( ) = 0;//�ŗL����
protected:
	//set�n
	void setTx( int tx );//�摜�����W
	void setTy( int ty );//�摜�����W
private:
	double _x;
	double _y;
	int _tx;
	int _ty;
};


