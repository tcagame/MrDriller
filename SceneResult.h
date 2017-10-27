#pragma once
#include "Scene.h"

class SceneResult : public Scene {
public:
	SceneResult( );
	virtual ~SceneResult( );
public:
	SCENE update( );
	void draw( ) const;
};