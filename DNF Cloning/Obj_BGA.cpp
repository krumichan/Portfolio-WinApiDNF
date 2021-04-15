#include "Obj_BGA.h"
#include "st.h"

Object_Background* Object_Background::Create()
{
	Object_Background* p = new Object_Background;
	p					-> Init( SingleTon::Call()->GetBMP( IDB_BGA ) );
	return p;	
}

void Object_Background::Dealloc()
{
	DeleteObject( ResourceBMP );
}

void Object_Background::Render()
{
	HDC			 B = SingleTon::Call()->m_hBackDC;
	HDC			 M = SingleTon::Call()->m_hMemDC;
	SelectObject ( M, ResourceBMP );
	BitBlt		 ( B, 0, 0, 1440, 600, M, 0, 0, SRCCOPY );
}