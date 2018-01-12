#pragma once
#include "Scene.h"

class SceneModeSelect : public Scene {
public:
	SceneModeSelect( );
	virtual ~SceneModeSelect( );
public:
	SCENE update( );
	void draw( ) const;
};

