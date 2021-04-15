#pragma once
#include "Object.h"

class Object_Bullet : public Object {
protected:
public:
			HitInform	  m_Hit;
	virtual void		  Init( HBITMAP _res );
			void		  Render();
			void		  Update( float dt );
};