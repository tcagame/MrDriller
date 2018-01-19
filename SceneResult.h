#pragma once
#include "Scene.h"

class SceneResult : public Scene {
public:
	SceneResult( );
	virtual ~SceneResult( );
public:
	SCENE update( );
	void draw( ) const;
	private:
	int _img_handle;
	//int _se[ 18 ];
};