#pragma once
#include "Header.h"

class Object {

protected:
	HBITMAP			ResourceBMP;
	CGPosition		Position;
	DIRECTION		direction;
	float			m_fZ;
	bool			m_bActive;
	float			m_fRadius;
	OBJECTS			m_iTag;
public:
	virtual void	Init( HBITMAP _Res );

	virtual void	Render()		= 0;
	virtual void	Update(float dt) = 0;
	virtual void	dealloc() {;}

	CGPosition		GetPosition()				{ return	Position;	}
	void			SetPosition(CGPosition _Pos){ Position	= _Pos;		}
	DIRECTION		GetDirection()				{ return	direction;	}
	void			SetDirection(DIRECTION _Dir){ direction	= _Dir;		}
	float			GetZ()						{ return	m_fZ;		}
	void			SetZ(float _Z)				{ m_fZ		= _Z;		}
	bool			GetActive()					{ return	m_bActive;	}
	void			SetActive( bool _act )		{ m_bActive = _act;		}
	float			GetRadius()					{ return	m_fRadius;  }
	void			SetRadius( float _rad )		{ m_fRadius = _rad;		}
	OBJECTS			GetTag()					{ return	m_iTag;		}
	void			SetTag( OBJECTS _tag )		{ m_iTag	= _tag;		}
};