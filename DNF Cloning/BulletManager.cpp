#include "BulletManager.h"
#include "st.h"

void BulletManager::Init( Scene* _Scene )
{
	if( m_hResource == NULL )
		m_hResource  = SingleTon::Call()->GetBMP( IDB_BULLET );
	for( int i = 0; i < MAX_BULLET; i++ ) {
		m_pBullet[i] = new Object_Bullet;
		m_pBullet[i]->Init( m_hResource );
		m_pBullet[i]->SetZ( 123.f );
		m_pBullet[i]->SetActive( false );
		_Scene->add_Obj( m_pBullet[i] );
	}
}
void BulletManager::addBullet( CGPosition _pos, DIRECTION _dir, HitInform _hi )
{
	for( int i = 0; i < MAX_BULLET; i++ ) {
		if( m_pBullet[i] == NULL ) continue;
		if( m_pBullet[i]->GetActive() ) continue;
		m_pBullet[i]->m_Hit = _hi;
		m_pBullet[i]->SetActive( true );
		m_pBullet[i]->SetPosition( _pos );
		m_pBullet[i]->SetDirection( _dir );
		SingleTon::Call()->SM.play( SND_FIRE );
		break;
	}
}
void BulletManager::UseRateDisplay( CGPosition _pos )
{
	HDC	 B			= SingleTon::Call()->m_hBackDC;
	float UseCount	= 0;
	TCHAR buf[256]	= { 0 };

	for( int i = 0; i < MAX_BULLET; i++ ) {
		if( m_pBullet[i] == NULL ) continue;
		if( m_pBullet[i]->GetActive() ) {
			 SingleTon::Call()->ChangeBRUSH( 1 );
			 UseCount++;
		}
		else SingleTon::Call()->ChangeBRUSH( 2 );

		Rectangle( B, _pos.x + i * 15, _pos.y, _pos.x + i * 15 + 15, _pos.y + 15 );
	}

	_stprintf_s( buf, L"Bullet : %2.2f %%", UseCount/(float)MAX_BULLET * 100.f );
	TextOut( B, MAX_BULLET * 15 + 25, 12, buf, _tcslen(buf) );

	SingleTon::Call()->ResetGDIOBJECT();
}