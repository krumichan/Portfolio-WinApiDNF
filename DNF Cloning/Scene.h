#pragma once
#include "Object.h"

#define MAX_OBJ		512	

class Scene {
protected:
			Object*	Obj_List[ MAX_OBJ ];
public:
	virtual void		Init();
	virtual void		run( float dt );
			void		dealloc();
			void		add_Obj( Object* _Obj );
			void		add_Obj( Object* _Obj, OBJECTS _tag );
			Object*		GetChildByTag( OBJECTS _tag );
};