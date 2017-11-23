#pragma once
#include <memory>
#include "Player.h"

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

