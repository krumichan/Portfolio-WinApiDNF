#include "EnemyManager.h"
#include "st.h"

void EnemyManager::Init( Scene* _Scene )
{
	if( m_hEnemyResource == NULL )
		m_hEnemyResource  = SingleTon::Call()->GetBMP( IDB_ENEMY );
	for( int i = 0; i < MAX_ENEMY; i++ ) {
		m_pEnemy[i] = new Object_Enemy;
		m_pEnemy[i]->Init( m_hEnemyResource );
		m_pEnemy[i]->SetActive( false );
		_Scene->add_Obj( m_pEnemy[i] );
	}
}
void EnemyManager::addEnemy( CGPosition _pos )
{
	for( int i = 0; i < MAX_ENEMY; i++ ) {
		if( m_pEnemy[i] == NULL ) continue;
		if( m_pEnemy[i]->GetActive() ) continue;
		m_pEnemy[i]->SetActive( true );
		m_pEnemy[i]->InitPosition( _pos );
		break;
	}
}
bool EnemyManager::HitCheck( CGPosition _pos, float _Radius, DIRECTION _dir, HitInform hi )
{
	for( int i = 0; i < MAX_ENEMY; i++ ) {
		if( m_pEnemy[i] == NULL ) continue;
		if( !m_pEnemy[i]->GetActive() ) continue;
		CGPosition pos		 = m_pEnemy[i]->GetPosition();
		VectorInformation VI = SingleTon::Call()->Distance( _pos, pos );
		
		if( VI.distance < _Radius + m_pEnemy[i]->GetRadius() ) {
			m_pEnemy[i]->Hit( _dir, hi );

			if( hi.type == HT_BULLET )
				return true;
		}
	}
	return false;
}

void EnemyManager::UseRateDisplay( CGPosition _pos )
{
	HDC	  B		   = SingleTon::Call()->m_hBackDC;
	float  UseEnemy = 0.f;
	TCHAR buf[256] = { 0 };

	for( int i = 0; i < MAX_ENEMY; i++ ) {
		if( m_pEnemy[i] == NULL ) continue;
		if( m_pEnemy[i]->GetActive() ) {
			SingleTon::Call()->ChangeBRUSH( 1 );
			UseEnemy++;
		}
		else
			SingleTon::Call()->ChangeBRUSH( 2 );

		Rectangle( B, _pos.x + i * 15, _pos.y, _pos.x + i * 15 + 15, _pos.y + 15  );
	}
	_stprintf_s(buf, L"Enemy : %2.2f %% ", UseEnemy / (float)MAX_ENEMY * 100.f );
	TextOut( B, 10 + MAX_ENEMY * 15 + 15, 32, buf, _tcslen(buf) );

	for( int i = 0; i < MAX_ENEMY; i++ ) {
		if( m_pEnemy[i] == NULL ) continue;
		if( m_pEnemy[i]->GetActive() == false ) continue;

		SingleTon::Call()->ChangePEN( 4 );
		CGPosition pos  = m_pEnemy[i]->GetPosition();
		//CGPosition Size = m_pEnemy[i]->m_srcSize; 
		
		for( int j = 0; j < m_pEnemy[i]->m_nMaxHp; j++ ) {
			SingleTon::Call()->ChangeBRUSH( 2 );
			Rectangle( B, pos.x + j*5 - 20, pos.y - 130, pos.x +j*5 + 5 - 19, pos.y + 5 - 130 );
		}
		for( int j = 0; j < m_pEnemy[i]->m_nHP; j++ ) {
			SingleTon::Call()->ChangeBRUSH( 1 );
			Rectangle( B, pos.x + j*5 - 20, pos.y - 130, pos.x +j*5 + 5 - 19, pos.y + 5 - 130 );
		}
	}

	SingleTon::Call()->ResetGDIOBJECT();
}