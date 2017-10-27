#pragma once
class Scene {
public:
	enum SCENE {
		SCENE_TITLE,
		SCENE_PLAY,
		SCENE_RESULT
	};
public:
	Scene( );
	virtual ~Scene( );
public:
	virtual SCENE update( ) = 0;
	virtual void draw( ) = 0;
};

