#include "SoundManager.h"

void SoundManager::Init()
{
	r = System_Create( &pSystem );
	errorCheck( r );

	r = pSystem->init( 100, FMOD_INIT_NORMAL, NULL );
	errorCheck( r );
}

void SoundManager::loading()
{
	r = pSystem->createSound( "forest01.mp3", FMOD_LOOP_NORMAL, NULL, &pSnd[SND_BGM] );
	errorCheck( r );
	r = pSystem->createSound( "walk.wav", FMOD_DEFAULT, NULL, &pSnd[SND_WALK] );
	errorCheck( r );
	r = pSystem->createSound( "jump.wav", FMOD_DEFAULT, NULL, &pSnd[SND_JUMP] );
	errorCheck( r );
	r = pSystem->createSound( "land.wav", FMOD_DEFAULT, NULL, &pSnd[SND_LAND] );
	errorCheck( r );
	r = pSystem->createSound( "attackgun01.wav", FMOD_DEFAULT, NULL, &pSnd[SND_FIRE] );
	errorCheck( r );
	r = pSystem->createSound( "attack1.wav", FMOD_DEFAULT, NULL, &pSnd[SND_HIT] );
	errorCheck( r );
	r = pSystem->createSound( "mach_hit.ogg", FMOD_DEFAULT, NULL, &pSnd[SND_HIT2] );
	errorCheck( r );
	r = pSystem->createSound( "kick.wav", FMOD_DEFAULT, NULL, &pSnd[SND_KICK] );
	errorCheck( r );

}
void SoundManager::play(int _type)
{
	pSystem->update();
	pSystem->playSound( FMOD_CHANNEL_FREE, pSnd[_type], false, &pCh[_type] );
}
void SoundManager::stop(int _ch)
{
	pCh[_ch]->stop();
}
void SoundManager::errorCheck( FMOD_RESULT _r )
{
	if( _r != FMOD_OK ) {
		TCHAR szStr[512] = { 0 };
		const char* errorMessage = FMOD_ErrorString(_r);
		MultiByteToWideChar( CP_ACP, NULL, errorMessage, -1, szStr, 512 );
		MessageBox( NULL, szStr, L"FMOD error", MB_OK );
	}
}