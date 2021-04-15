#pragma once
#include "Header.h"
#include "Obj_Enemy.h"
#include "Scene.h"

#define	MAX_ENEMY	16

class EnemyManager {

public:
	Object_Enemy*	m_pEnemy[ MAX_ENEMY ];
	HBITMAP			m_hEnemyResource;
	EnemyManager()
	{
		memset( m_pEnemy, NULL, sizeof(m_pEnemy) );
		m_hEnemyResource = NULL;
	}
public:
	void Init			( Scene* _Scene );
	void addEnemy		( CGPosition _pos );
	bool HitCheck		( CGPosition _pos, float _Radius, DIRECTION _dir, HitInform hi );
	void UseRateDisplay	( CGPosition _pos );
};