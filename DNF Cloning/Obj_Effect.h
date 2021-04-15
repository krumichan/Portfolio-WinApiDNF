#pragma once
#include "Object.h"

class Object_Effect : public Object 
{
protected:
			int			m_iFrame;
			float		m_fFrameDelay;
			EffectInfo	ei;
public:
			void		InitWithEffect();
	virtual void		Render();
	virtual void		Update( float dt );
	virtual void		dealloc();
			void		SetEffectInfo( EffectInfo );
};