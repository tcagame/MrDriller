#pragma once


class Player {
public:
	Player( int x, int y );
	~Player( );
public:
	void update( );
	void draw( );
public://getŒn
	int getAir( );
private:
	int _air;
};