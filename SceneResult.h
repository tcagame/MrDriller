#pragma once
#include "Scene.h"

class SceneResult : public Scene {
public:
	SceneResult( int score, int depth );
	virtual ~SceneResult( );
public:
	SCENE update( );
	void draw( ) const;
	void drawDepth( ) const;
	void drawScore( ) const;
	private:
	int _img_handle;
	int _img_num;
	int _score;
	int _depth;
	//int _se[ 18 ];
};