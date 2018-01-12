#pragma once
#include "Scene.h"
#include "Game.h"

class SceneModeSelect : public Scene {
public:
	SceneModeSelect( Game::MODE* mode );
	virtual ~SceneModeSelect( );
public:
	SCENE update( );
	void draw( ) const;
private:
	int _image_mode;
	Game::MODE* _select;
	int _count;
};