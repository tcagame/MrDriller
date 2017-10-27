#pragma once
#include "Scene.h"

class SceneResult : public Scene {
public:
	SceneResult( );
	~SceneResult( );
public:
	SCENE update( );
	void draw( );
};