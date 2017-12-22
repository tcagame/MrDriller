#pragma once

const int FPS = 60;

class FpsController {
public:
	FpsController( );
	virtual ~FpsController( );
public:
	void update( );
	bool isOverFps( ) const;
	double getFps( ) const;
private:
	void init( );
private:
	int _before_time;
	int _count;
	int _wait_time;
	double _fps;
};

