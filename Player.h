#pragma once


class Player {
public:
	Player( int x, int y );
	~Player( );
public:
	void update( );
	void draw( );
public://get�n
	int getAir( );
private:
	int _air;
};