#pragma once
#include "Object.h"

class Object_Hero : public Object {

protected:
	CGPosition	m_srcPos;
	CGPosition	m_srcSize;
	CGPosition	m_offset;
	HitInform	m_Hit[2];
	STATE		iState;
	STATE		iPrevState;
	int			iFrame;
	float		fFrameDelay;
	float		m_fMoveDelay;
	float		m_fVelocity; // ¿Ã¶ó°¡´Â Èû
	float		fWalkDelay;
	bool		m_bMoveHold;
	bool		m_fFired;
	bool		m_breFired;
	bool		m_bKickAttack;
	
public:
	virtual void		Init( HBITMAP _Res );

	static Object_Hero* Create();
	virtual void		Dealloc();
	void				Render();
	void				Update(float dt);
	void				Animation( float dt );
	void				Action( float dt );
};	
