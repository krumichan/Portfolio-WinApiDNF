#include "Obj_Enemy.h"
#include "st.h"

void Object_Enemy::Init( HBITMAP _res )
{
	Object::Init( _res );
	m_srcPos					= ccp( 0, 0 );
	m_srcSize					= ccp( 0, 0 );
	m_offset					= ccp( 0, 0 );
	m_iState					= IDLE;
	m_fRadius					= 20.f;
	m_pTarget					= NULL;
	m_fGroggyDelay				= 0.f;
	m_bSetRandomDestination		= false;
	m_DestinationPosition		= ccp( 0, 0 );
	m_fMoveDelay				= SingleTon::Call()->Random( 50, 200 );
	m_InterpolateMovementOrigin = ccp( 0, 0 );
	m_nHP						= 10;
	m_nMaxHp					= 10;
	m_fTime						= 0.f;
}
void Object_Enemy::Render()
{
	HDC			B	= SingleTon::Call()->m_hBackDC;
	HDC			M	= SingleTon::Call()->m_hMemDC;
	CGPosition	pos = this->GetPosition();

	pos.x += m_offset.x;
	pos.y += m_offset.y + this->GetZ();

	SelectObject	( M, ResourceBMP );
	BitBlt			( B, 
					  pos.x, pos.y, 
					  m_srcSize.x, m_srcSize.y, 
					  M, 
					  m_srcPos.x, 
					  m_srcPos.y + m_srcSize.y, 
					  SRCAND   );
	BitBlt			( B, 
					  pos.x, pos.y,
					  m_srcSize.x, m_srcSize.y, 
					  M, 
					  m_srcPos.x,
					  m_srcPos.y, 
					  SRCPAINT );
}
void Object_Enemy::Update( float dt )
{
	m_fTime += dt * 2;
	this->SetZ( sinf(m_fTime) * 10 );

	this->Action			( dt );
	this->Animation			( dt );
	this->InterpolateMoving	( dt );

	this->DebugDraw			();
}
void Object_Enemy::Hit( DIRECTION _dir, HitInform hi )
{
	if( hi.type == HT_BULLET ) {
		SingleTon::Call()->SM.play( SND_HIT  );
		SingleTon::Call()->EfM.addEffect( this->GetPosition(), EF_BLOOD, _dir );
	}
	else if( hi.type == HT_KICK ) {
		SingleTon::Call()->SM.play( SND_HIT2 );
		CGPosition pos = this->GetPosition();
		pos.x += ( _dir == RIGHT ? -120 : 0 );
		SingleTon::Call()->EfM.addEffect( pos, EF_HIT, _dir );
	}

	m_fGroggyDelay	= hi.groggyDelay;
	m_iState		= HIT;
	_dir == RIGHT ? m_InterpolateMovementOrigin.x += hi.outDis : m_InterpolateMovementOrigin.x -= hi.outDis;
	m_InterpolateMovementOrigin = SingleTon::Call()->PointAdjustment( m_InterpolateMovementOrigin );

	if( --m_nHP <= 0 ) {
		SetActive( false );
		return;
	}
}
void Object_Enemy::Action( float dt )
{
	if( m_pTarget == NULL ) {
		m_pTarget = SingleTon::Call()->m_pNowRunningScene->GetChildByTag( HERO );
	}
	
	CGPosition myPos		= this->GetPosition();
	CGPosition tarPos		= m_pTarget->GetPosition();
	VectorInformation vi	= SingleTon::Call()->Distance( tarPos, myPos );

	if( m_fGroggyDelay <= 0.f )
		if( vi.distance < 300 ) m_iState = WALK;

	switch( m_iState ) 
	{
	case IDLE:
		{
			if( m_bSetRandomDestination == false ) {
				m_DestinationPosition.x = SingleTon::Call()->Random( myPos.x - 100, myPos.x + 100 );
				m_DestinationPosition.y = SingleTon::Call()->Random( myPos.y - 100, myPos.y + 100 );
				if( !SingleTon::Call()->PointExit(m_DestinationPosition) )
					m_bSetRandomDestination = true;
			}
			if( SingleTon::Call()->Random(0, 500) == 0 ) m_iState = WALK;
			break;
		}
	case WALK:
		{
			m_bSetRandomDestination = false;
			if( vi.distance > 300 )
				vi = SingleTon::Call()->Distance( m_DestinationPosition, myPos );
			if( vi.distance < 10  ) {
				m_iState = IDLE;
				break;
			}
			m_InterpolateMovementOrigin.x += vi.vec.x * m_fMoveDelay * dt;
			m_InterpolateMovementOrigin.y += vi.vec.y * m_fMoveDelay * dt;
			
			this->SetDirection	( vi.vec.x < 0 ? LEFT : RIGHT );
			break;
		}
	case HIT:
		{
			m_fGroggyDelay -= dt;
			if( m_fGroggyDelay <= 0 ) {
				m_iState = IDLE;
			}
			break;
		}
	}
}
void Object_Enemy::Animation( float dt )
{
	switch( m_iState ) 
	{
	case IDLE: 
		m_srcSize	= ccp( 79, 100 );
		m_srcPos	= ccp( this->GetDirection() == RIGHT ? 1 : 81, 2 );
		break;
	case WALK:
		m_srcSize	= ccp( 87, 79 );
		m_srcPos	= ccp( this->GetDirection() == RIGHT ? 161 : 249, 3 );
		break;
	case HIT:
		m_srcSize	= ccp( 76, 120 );
		m_srcPos	= ccp( this->GetDirection() == RIGHT ? 337 : 414, 2 );
		break;
	}
		m_offset	= ccp( -m_srcSize.x/2, -m_srcSize.y-20 );
}

void Object_Enemy::DebugDraw()
{
	HDC			B	= SingleTon::Call()->m_hBackDC;
	CGPosition	pos = this->GetPosition();
	
	SingleTon::Call()->ChangeBRUSH	( 0 );
	SingleTon::Call()->ChangePEN	( 0 );

	Ellipse		( B, pos.x - m_fRadius, pos.y - m_fRadius , 
					 pos.x + m_fRadius, pos.y + m_fRadius );
	Ellipse		( B, m_InterpolateMovementOrigin.x - 3, m_InterpolateMovementOrigin.y - 3 ,
					 m_InterpolateMovementOrigin.x + 3, m_InterpolateMovementOrigin.y + 3 );

	MoveToEx	( B, pos.x, pos.y, NULL );
	LineTo		( B, m_InterpolateMovementOrigin.x, m_InterpolateMovementOrigin.y );

	SingleTon::Call()->ChangePEN( 1 );
	Rectangle	( B, pos.x + 30, pos.y, pos.x + 180, pos.y + 68 );
	
	TCHAR posInform[64]		= { 0 };
	TCHAR stateInform[64]	= { 0 };
	TCHAR HPInform[64]		= { 0 };
	TCHAR ZInform[64]		= { 0 };
	_stprintf_s( posInform	, L"X :%4.2f. Y:%4.2f"	, pos.x, pos.y	);
	_stprintf_s( stateInform, L"State : %s"			, SingleTon::Call()->IntToStateString( m_iState ) );
	_stprintf_s( HPInform	, L"HP:%d"				, m_nHP			);
	_stprintf_s( ZInform	, L"Z :%2.2f"			, -this->GetZ()	);

	TextOut		( B, pos.x + 33, pos.y + 18, stateInform	, _tcslen(stateInform) );
	SetTextColor( B, RGB(255, 128, 0) );

	TextOut		( B, pos.x + 33, pos.y + 3 , posInform	, _tcslen(posInform)   );
	TextOut		( B, pos.x + 33, pos.y + 33, HPInform	, _tcslen(HPInform)    );
	TextOut		( B, pos.x + 33, pos.y + 48, ZInform		, _tcslen(ZInform) );
		
	SingleTon::Call()->ResetGDIOBJECT();
}