#pragma once


class Player {
public:
	Player( int x, int y );
	virtual ~Player( );
public:
	void update( );
	void draw( );
	void drawDeathAnimation( );
	bool death( );
public://getån
	int getAir( );
private:
	int _air;
	int _img_handle;
	int _count;
	int _anime_time;
};