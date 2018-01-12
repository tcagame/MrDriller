#pragma once
#include "Scene.h"

class SceneTitle : public Scene {
public:
	SceneTitle( );
	virtual ~SceneTitle( );
public:
	SCENE update( );
	void draw( ) const;
private:
	int _img_handle;
	int _se[ 18 ];
};