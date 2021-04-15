#pragma once
#include "Scene.h"

class Scene_Tower : public Scene {
protected:
public:
	static Scene_Tower* scene ();
	void				Init  ();
	virtual void		run   ( float );
};