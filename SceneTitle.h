#pragma once
#include "Scene.h"

class SceneTitle : public Scene {
public:
	SceneTitle( );
	virtual ~SceneTitle( );
public:
	SCENE update( );
	void draw( ) const;
};