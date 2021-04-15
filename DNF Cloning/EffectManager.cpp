#include "EffectManager.h"
#include "st.h"

EffectManager::EffectManager()
{
	memset( m_pEffect, NULL, sizeof(m_pEffect) );
}
void EffectManager::Init( Scene* _scene )
{
	m_EffectInfo[ EF_BLOOD ].resource	= SingleTon::Call()->GetBMP( IDB_BLOOD );
	m_EffectInfo[ EF_BLOOD ].delay		= 0.04f;
	m_EffectInfo[ EF_BLOOD ].MaxFrame	= 7;
	m_EffectInfo[ EF_BLOOD ].offset		= ccp( 0.f, 0.f );
	m_EffectInfo[ EF_BLOOD ].srcSize	= ccp( 40, 73 );
	m_EffectInfo[ EF_BLOOD ].anotherDirectionPos = 280;
	
	m_EffectInfo[ EF_HIT ].resource		= SingleTon::Call()->GetBMP( IDB_HIT );
	m_EffectInfo[ EF_HIT ].delay		= 0.1f;
	m_EffectInfo[ EF_HIT ].MaxFrame		= 3;
	m_EffectInfo[ EF_HIT ].offset		= ccp( 0.f, 0.f );
	m_EffectInfo[ EF_HIT ].srcSize		= ccp( 127, 118 );
	m_EffectInfo[ EF_HIT ].anotherDirectionPos = 381;

	for( int i = 0; i < MAX_EFFECT; i++ ) {
		m_pEffect[i] = new Object_Effect;
		m_pEffect[i]->InitWithEffect();
		m_pEffect[i]->SetActive( false );
		_scene->add_Obj( m_pEffect[i] );
	}
}
void EffectManager::addEffect( CGPosition _pos, int _type, DIRECTION _dir )
{    
	for( int i = 0; i < MAX_EFFECT; i++ ) {
		if( m_pEffect[i] == NULL ) continue;
		if( m_pEffect[i]->GetActive() ) continue;

		m_pEffect[i]->SetZ			( SingleTon::Call()->Random( 100, 150 ) );
		m_pEffect[i]->SetActive		( true );
		m_pEffect[i]->SetDirection	( _dir );
		m_pEffect[i]->SetPosition	( _pos );
		m_pEffect[i]->SetEffectInfo ( m_EffectInfo[_type] );
		break;
	}
}
