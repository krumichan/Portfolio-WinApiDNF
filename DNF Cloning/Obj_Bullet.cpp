#include "Obj_Bullet.h"
#include "st.h"

void Object_Bullet::Init( HBITMAP _res ) 
{
	Object::Init( _res );
	m_fRadius	= 20.f;
}
void Object_Bullet::Render()
{
	HDC			B	= SingleTon::Call()->m_hBackDC;
	HDC			M	= SingleTon::Call()->m_hMemDC;
	CGPosition	pos = this->GetPosition();
	float		Z	= this->GetZ();
	pos.y		   -= Z;

	SelectObject	( M, ResourceBMP );
	BitBlt			( B, pos.x, pos.y, 18, 6, M, 0, 6, SRCAND   );
	BitBlt			( B, pos.x, pos.y, 18, 6, M, 0, 0, SRCPAINT );
}
void Object_Bullet::Update( float dt )
{
	CGPosition pos = this->GetPosition();

	if( this->GetDirection() == RIGHT ) {
		pos.x += 1000.f * dt;
	}
	else {
		pos.x -= 1000.f * dt;
	}
	if( SingleTon::Call()->EM.HitCheck(pos, this->GetRadius(), this->GetDirection(), m_Hit) ) 
	{
		this->SetActive( false );
		return;
	}

	if( SingleTon::Call()->PointExit(pos) )
		this->SetActive( false );

	this->SetPosition( pos );
}