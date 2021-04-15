#include "Obj_Hero.h"
#include "st.h"

Object_Hero* Object_Hero::Create()
{
	Object_Hero *p	= new Object_Hero;
	p				->Init( SingleTon::Call()->GetBMP( IDB_HERO ) );
	return p;
}

void Object_Hero::Dealloc()
{
	DeleteObject( ResourceBMP );
}

void Object_Hero::Init( HBITMAP _Res )
{
	Object::Init( _Res );
	m_srcPos		= ccp(0, 0);
	m_srcSize		= ccp(0, 0);
	m_offset		= ccp(0, 0);
	iState			= IDLE;
	iPrevState		= IDLE;
	iFrame			= 0;
	fFrameDelay		= 0.f;
	m_fVelocity		= 0.f;
	fWalkDelay		= 0.f;
	m_fMoveDelay	= 300.f;
	m_bMoveHold		= false;
	m_fFired		= false;
	m_breFired		= false;
	m_bKickAttack	= false;

	m_Hit[0].type			= HT_BULLET;
	m_Hit[0].groggyDelay	= 1.f;
	m_Hit[0].outDis			= 100.f;

	m_Hit[1].type			= HT_KICK;
	m_Hit[1].groggyDelay	= 3.f;
	m_Hit[1].outDis			= 200.f;
}

void Object_Hero::Render()
{
	HDC		   B   = SingleTon::Call()->m_hBackDC;
	HDC		   M   = SingleTon::Call()->m_hMemDC;
	CGPosition pos = this->GetPosition();
	float	   Z   = this->GetZ();

	pos.x		  -= m_srcSize.x * m_offset.x;
	pos.y		  -= Z + m_srcSize.y * m_offset.y;

	SelectObject( M, ResourceBMP );
	BitBlt		( B,
			      pos.x, pos.y,
			      m_srcSize.x, m_srcSize.y, 
			      M,
			      m_srcPos.x + m_srcSize.x * iFrame,
			      m_srcPos.y + m_srcSize.y, 
			      SRCAND); // AND 연산

	BitBlt		( B,
			      pos.x, pos.y, 
	  		      m_srcSize.x, m_srcSize.y, 
			      M, 
			      m_srcPos.x + m_srcSize.x * iFrame,
			      m_srcPos.y, 
			      SRCPAINT); // OR 연산
}

void Object_Hero::Update(float dt)
{
		Action	 ( dt );
		Animation( dt );
}

void Object_Hero::Animation( float dt )
{
	CGPosition pos = this->GetPosition();

	if( iState != ATTACK && iState != KICK ) {
		if( iState != JUMP && iState != DROP )
			iState  = IDLE;
		if( GetAsyncKeyState(VK_LEFT) )
		{
			pos.x -= m_fMoveDelay * dt;
			if( iState != JUMP && iState != DROP ) iState = WALK;
			SetDirection(LEFT);
		}
		if( GetAsyncKeyState(VK_RIGHT) )
		{
			pos.x += m_fMoveDelay * dt;
			if( iState != JUMP && iState != DROP ) iState = WALK;
			SetDirection(RIGHT);
		}
		if( GetAsyncKeyState(VK_UP) )
		{
			pos.y -= m_fMoveDelay * dt;
			if( iState != JUMP && iState != DROP ) iState = WALK;
		}
		if( GetAsyncKeyState(VK_DOWN) )
		{
			pos.y += m_fMoveDelay * dt;
			if( iState != JUMP && iState != DROP ) iState = WALK;
		}
		if( GetAsyncKeyState('C') ) {
			if( iState != JUMP && iState != DROP ) iState = JUMP;
		}
	}

	if( GetAsyncKeyState('X') ) {
		if( iState != JUMP && iState != DROP ) 
		{
			m_breFired = true;
			iState	   = ATTACK;
		}
	}
	if( GetAsyncKeyState('S') ) {
		if( iState != JUMP && iState != DROP )
		{
			if( iPrevState != KICK )
				iState = KICK;
		}
	}

	if( m_bMoveHold == false ) 
		this->SetPosition( SingleTon::Call()->PointAdjustment( pos ) );

	if( iState != iPrevState ) {
		fFrameDelay	= 0;
		iFrame		= 0;
		iPrevState	= iState;
	}
}
void Object_Hero::Action( float dt )
{
	switch (iState)
	{
	case IDLE:
		{
			m_srcPos	= ccp(this->GetDirection() == RIGHT ? 0 : 610, 10);
			m_srcSize	= ccp(54, 144);
			m_offset	= ccp( 0.5f, 1.f );

			fFrameDelay += dt;
			if (fFrameDelay > 0.1f)
			{
				fFrameDelay = 0.f;
				iFrame++;
				if (iFrame > 3) iFrame = 0;
			}
			break;
		}
	case WALK:
		{
			m_srcPos	= ccp(this->GetDirection() == RIGHT ? 0 : 610, 310);
			m_srcSize	= ccp( 75, 143 );
			m_offset	= ccp( 0.5f, 1.f );

			fWalkDelay	+= dt;
			if( fWalkDelay > 0.4f ) {
				fWalkDelay = 0.f;
				SingleTon::Call()->SM.play( SND_WALK );
			}

			fFrameDelay += dt;
			if (fFrameDelay > 0.1f)
			{
				fFrameDelay = 0.f;
				iFrame++;
				if (iFrame > 7) iFrame = 0;
			}
			break;
		}
	case JUMP:
		{
			m_srcPos	 = ccp(this->GetDirection() == RIGHT ? 0 : 610, 610);
			m_srcSize	 = ccp(85, 135);
			m_offset	 = ccp( 0.5f, 1.f );

			fFrameDelay += dt;

			if( fFrameDelay < 0.1f ) {
				m_fVelocity = VELOCITY;
				m_bMoveHold = true;
				break;
			}
			if( m_bMoveHold == true ) {
				m_bMoveHold  = false;
				SingleTon::Call()->SM.play( SND_JUMP );
			}
			m_fVelocity -= GRAVITY * dt;
			m_fZ		+= m_fVelocity * dt;

			if( fFrameDelay >= 0.1f ) iFrame	  = 1;
			if( fFrameDelay >= 0.2f ) iFrame	  = 2;
			if( fFrameDelay >  0.3f ) fFrameDelay = 0.1f;

			if( m_fVelocity < 0 ) {
				m_fVelocity = 0.f;
				iState = DROP;
			}
			break;
		}
	case DROP:
		{
			m_srcPos	 = ccp(this->GetDirection() == RIGHT ? 0 : 610, 610);
			m_srcSize	 = ccp(85, 135);
			m_offset	 = ccp( 0.5f, 1.f );

			fFrameDelay += dt;

			if( m_fZ > 0 ) {
				m_fVelocity += GRAVITY * dt;
				m_fZ		-= m_fVelocity * dt;

				iFrame		 = 3;
				if( fFrameDelay > 0.1f ) iFrame		 = 4;
				if( fFrameDelay > 0.2f ) fFrameDelay = 0.f;
			}
			else {
				m_fZ			= 0.f;
				if( m_bMoveHold == false ) {
					m_bMoveHold	= true;
					fFrameDelay = 0;
					SingleTon::Call()->SM.play( SND_LAND );
					break;
				}
				iFrame = 5;
				if( fFrameDelay > 0.1f ) iFrame = 6;
				if( fFrameDelay > 0.2f ) {
					iState		= IDLE;
					m_bMoveHold = false;
				}
			}
			break;
		}
	case ATTACK:
		{
			m_srcPos		= ccp( this->GetDirection() == RIGHT ? 0 : 610, 910 );
			m_srcSize		= ccp( 122, 155 );
			m_offset		= ccp( this->GetDirection() == RIGHT ? 0.2f : 0.8f, 1.f );

			fFrameDelay	   += dt;
			if( fFrameDelay > 0.1f ) iFrame = 1;
			if( fFrameDelay > 0.2f ) iFrame = 2;
			if( fFrameDelay >= 0.3f && fFrameDelay <= 0.35f ) 
			{
				iFrame = 3;
				if( m_fFired == false ) {
					m_breFired		= false;
					m_fFired		= true;
					CGPosition pos	= this->GetPosition();
					pos.x += this->GetDirection() == RIGHT ? 95.f : -95.f;
					SingleTon::Call()->BM.addBullet( pos, this->GetDirection(), m_Hit[0] );
				}
			}
			if( fFrameDelay > 0.4f ) {
				if( m_breFired ) {
					m_fFired	= false;
					fFrameDelay = 0.3f;
				}
				iFrame		= 4;
			}
			if( fFrameDelay > 0.5f ) {
				m_fFired	= false;
				iState		= IDLE;
			}
			break;
		}
	case KICK:
		{
			m_srcPos	= ccp( 0, this->GetDirection() == RIGHT ? 1300 : 1600 );
			m_srcSize	= ccp( 169, 130	);
			m_offset	= ccp( this->GetDirection() == RIGHT ? 0.2f : 0.6f, 1.f );

			fFrameDelay += dt;
			if( fFrameDelay > 0.1f ) {
				iFrame = 1;
				if( !m_bKickAttack ) {
					m_bKickAttack		 = true;
					CGPosition FirePos	 = this->GetPosition();
					FirePos.x			+= this->GetDirection() == RIGHT ? 95.f : -95.f;
					SingleTon::Call()->SM.play( SND_KICK );
					SingleTon::Call()->EM.HitCheck( FirePos, 50.f, this->GetDirection(), m_Hit[1] );
				}
			}
			if( fFrameDelay > 0.16f ) iFrame = 2;
			if( fFrameDelay > 0.18f ) iFrame = 3;
			if( fFrameDelay > 0.3f  ) iFrame = 4;
			if( fFrameDelay > 0.4f  ) {
				m_bKickAttack = false;
				iState		  = IDLE;
			}
			
			break;
		}
	}
}