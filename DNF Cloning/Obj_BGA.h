#pragma once
#include "Object.h"

class Object_Background : public Object {

public:
	static Object_Background* Create();
	virtual void			  Dealloc();
	void				  	  Render();
	void					  Update(float dt) { ; }
};