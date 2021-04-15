#pragma once
#include "Object.h"

class Object_Enemy : public Object {
protected:
	CGPosition		m_srcPos;
	CGPosition		m_srcSize;
	CGPosition		m_offset;
	CGPosition		m_DestinationPosition;
	CGPosition		m_InterpolateMovementOrigin;
	STATE			m_iState;
	Object*			m_pTarget;
	bool			m_bSetRandomDestination;
	float			m_fGroggyDelay;
	float			m_fMoveDelay;
	float			m_fTime;
public:
	int				m_nHP;
	int				m_nMaxHp;
public:
	virtual void	Init		( HBITMAP _res );
			void	InitPosition( CGPosition _pos )
					{
						this->SetPosition( _pos );
						m_fGroggyDelay				= 0.f;
						m_InterpolateMovementOrigin = _pos;
						m_DestinationPosition		= _pos;
					}
			void	Render				();
			void	Update				( float dt );
			void	Hit					( DIRECTION _dir, HitInform hi );
			void	Action				( float dt );
			void	Animation			( float dt );
			void	InterpolateMoving	( float dt ) 
					{
						CGPosition pos = this->GetPosition();
						CGPosition gap = ccp( m_InterpolateMovementOrigin.x - pos.x, m_InterpolateMovementOrigin.y - pos.y );
						if( fabsf(gap.x+gap.y) < 0.001f ) return;
						gap.x /= 64;
						gap.y /= 64;
						pos.x += gap.x;
						pos.y += gap.y;
						this->SetPosition( pos );
					}
			void	DebugDraw			();
};