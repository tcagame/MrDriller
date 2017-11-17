#pragma once
#include <memory>
#include "Player.h"

class Camera {
public:
	Camera( std::shared_ptr< Player > player );
	virtual ~Camera( );
public:
	void update( );
public:
	int getY( );
private:
	int _y;
	std::shared_ptr< Player > _player;
};

