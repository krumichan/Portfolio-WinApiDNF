#pragma once
#include "Scene.h"

class Scene_Title : public Scene {
protected:
public:
	static Scene_Title* scene();
	void				Init();
	void				run( float dt );
};