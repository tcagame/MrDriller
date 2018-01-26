#pragma once
#include <memory>
#include "Scene.h"

class Game {
public:
	enum MODE {
		MODE_NORMAL,
		MODE_BLIND,
		MAX_MODE,
	};
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
	MODE _mode;
	int _score;
	int _depth;
	int _level;
};
