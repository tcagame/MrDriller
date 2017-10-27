#pragma once


class Player {
public:
	Player( int x, int y );
	virtual ~Player( );
public:
	void update( );
	void draw( );
public://getŒn
	int getAir( );
private:
	int _air;
	int _img_handle;
	int _count;
};