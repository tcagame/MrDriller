#pragma once
#include "Scene.h"
#include "Game.h"

class SceneModeSelect : public Scene {
public:
	SceneModeSelect( Game::MODE* mode );
	virtual ~SceneModeSelect( );
public://åpè≥
	SCENE update( );
	void draw( ) const;
	void loadSound( );
	void loadGraph( );
private:
	Game::MODE* _select;
	int _count;
	bool _next;
};