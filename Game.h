#pragma once
#include <memory>
#include "Scene.h"

class Game {
public:
	Game( );
	virtual ~Game( );
public:
	void run( );
private:
	bool isLoop( ) const;
	void changeScene( Scene::SCENE scene );
private:
	std::shared_ptr< Scene > _scene;
	std::shared_ptr< class FpsController > _fps_ctrl;
	Scene::SCENE _now_scene;
};
