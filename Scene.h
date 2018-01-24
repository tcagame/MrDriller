#pragma once
#include "Sound.h"
#include "Graph.h"

class Scene {
public:
	enum SCENE {
		SCENE_TITLE,
		SCENE_MODE_SELECT,
		SCENE_PLAY,
		SCENE_RESULT
	};
public:
	Scene( );
	virtual ~Scene( );
public:
	virtual SCENE update( ) = 0;
	virtual void draw( ) const = 0;
	virtual void loadSound( ) = 0;
	virtual void loadGraph( ) = 0;
};

