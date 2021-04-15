#pragma once
#include "Obj_Effect.h"
#include "Scene.h"
#define MAX_EFFECT	64

enum EFFECT_TYPE {
	EF_BLOOD, EF_HIT
};

class EffectManager {
private:
	Object_Effect*	m_pEffect[ MAX_EFFECT ];
	EffectInfo		m_EffectInfo[ 2 ];
public:
					EffectManager();
	void			Init( Scene* _scene );
	void			addEffect( CGPosition _pos, int _type, DIRECTION _dir );
};