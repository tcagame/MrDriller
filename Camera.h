#pragma once
#include <memory>
#include "Player.h"

const int CAMERA_PLAYER_Y = 360 - 45;

class Camera {
public:
	Camera( );
	virtual ~Camera( );
public:
	void update( int player_y );
public:
	int getY( );
private:
	int _y;
	std::shared_ptr< Player > _player;
};

