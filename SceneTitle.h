#pragma once
#include "Scene.h"

class SceneTitle : public Scene {
public:
	SceneTitle( );
	~SceneTitle( );
public:
	SCENE update( );
	void draw( );
};