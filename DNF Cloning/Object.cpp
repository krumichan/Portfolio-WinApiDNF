#include "Object.h"

void Object::Init( HBITMAP _Res )
{
	ResourceBMP		= _Res;
	Position		= ccp(0, 0);
	direction		= RIGHT;
	m_fZ			= 0;
	m_bActive		= true;
	m_fRadius		= 0.f;
}