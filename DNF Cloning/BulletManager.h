#pragma once
#include "Header.h"
#include "Obj_Bullet.h"
#include "Scene.h"

#define	MAX_BULLET	16

class BulletManager {

public:
	Object_Bullet*	m_pBullet[ MAX_BULLET ];
	HBITMAP			m_hResource;
	BulletManager()
	{
		memset( m_pBullet, NULL, sizeof(m_pBullet) );
		m_hResource = NULL;
	}
public:
	void Init			( Scene* _Scene );
	void addBullet		( CGPosition _pos, DIRECTION _dir, HitInform _hi );
	void UseRateDisplay	( CGPosition _pos );
};