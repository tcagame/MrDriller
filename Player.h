#pragma once

enum DIR {
	DIR_LEFT,
	DIR_RIGHT
};

class Player {
public:
	Player( int x, int y );
	virtual ~Player( );
public:
	void update( );
	void draw( );
	void drawDeathAnimation( );
	bool death( );
	bool isStanding( ) const;
public://getån
	int getAir( );
private:
	void move( );
	void fall( );
private:
	int _air;
	int _img_handle;
	int _count;
	int _x;
	int _y;
	int _anime_time;
	bool _standing;
	enum DIR _direct;
};