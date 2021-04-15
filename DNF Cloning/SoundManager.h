#pragma once
#include "Header.h"
#include "fmod.hpp"
#include "fmod_errors.h"
#pragma comment ( lib, "fmodex_vc.lib" )
using namespace FMOD;

enum SOUNDINDEX {
	SND_BGM, SND_WALK, SND_JUMP, SND_LAND, 
	SND_FIRE, SND_HIT, SND_HIT2, SND_KICK,
	SND_SKILL
};

class SoundManager {

public:
	System*		pSystem;
	Channel*	pCh[10];
	Sound*		pSnd[10];
	FMOD_RESULT	r;

	void	Init();
	void	loading();
	void	play(int _type);
	void	stop(int _ch);
	void	errorCheck( FMOD_RESULT _r );
};