#include "Obj_Effect.h"
#include "st.h"

void Object_Effect::InitWithEffect()
{
	Object::Init( NULL );
	m_iFrame		= 0;
	m_fFrameDelay	= 0.f;
}
void Object_Effect::Render()
{
	HDC			B = SingleTon::Call()->m_hBackDC;
	HDC			M = SingleTon::Call()->m_hMemDC;
	CGPosition	pos = this->GetPosition();

	pos.y -= this->GetZ();
	pos.x += ei.offset.x;
	pos.y += ei.offset.y;

	int nDirXpos = this->GetDirection() == RIGHT ? 0 : ei.anotherDirectionPos;

	SelectObject( M, ResourceBMP );
	BitBlt( B,
			pos.x, pos.y,
			ei.srcSize.x, ei.srcSize.y,
			M,
			nDirXpos + ei.srcSize.x * m_iFrame, 
			ei.srcSize.y,
			SRCAND	 );
	BitBlt( B,
			pos.x, pos.y,
			ei.srcSize.x, ei.srcSize.y,
			M,
			nDirXpos + ei.srcSize.x * m_iFrame,
			0,
			SRCPAINT );
}
void Object_Effect::Update( float dt )
{
	m_fFrameDelay += dt;
	if( m_fFrameDelay > ei.delay ) {
		m_fFrameDelay = 0.f;
		m_iFrame++;
		if( m_iFrame >= ei.MaxFrame )
			this->SetActive( false );
	}
}
void Object_Effect::dealloc()
{
	DeleteObject( ResourceBMP );
}
void Object_Effect::SetEffectInfo( EffectInfo _ei )
{
	ei				= _ei;
	ResourceBMP		= ei.resource;
	m_iFrame		= 0;
	m_fFrameDelay	= 0;
}