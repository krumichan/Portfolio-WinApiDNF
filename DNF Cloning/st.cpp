#include "st.h"

SingleTon::SingleTon()
{
	m_pNowRunningScene = NULL;
}

SingleTon* SingleTon::Call()
{
	if( Instance == NULL ) Instance = new SingleTon;
	return Instance;
}

void SingleTon::CreateBackBuffer( HWND hWnd ) 
{
	m_hWnd			= hWnd;
	m_Instance		= (HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE);
	HDC hDC			= GetDC(hWnd);
	m_hBackDC		= CreateCompatibleDC(hDC);
	m_hMemDC		= CreateCompatibleDC(hDC);
	m_hBackBMP		= CreateCompatibleBitmap(hDC, 1440, 600);
	SelectObject	(m_hBackDC, m_hBackBMP);
	ReleaseDC		(hWnd, hDC);
	CreateGDIOBJECT	( );
}
void SingleTon::dealloc() 
{
	DeleteDC	(m_hBackDC);
	DeleteDC	(m_hMemDC);
	DeleteObject(m_hBackBMP);
}

HBITMAP SingleTon::GetBMP( int _Index )
{
	return LoadBitmap( m_Instance, MAKEINTRESOURCE(_Index) );
}
void SingleTon::replaceScene (Scene* _scene) 
{
	if( m_pNowRunningScene ) {
		m_pNowRunningScene->dealloc();
		delete m_pNowRunningScene;
	}
	m_pNowRunningScene = _scene;
}
int SingleTon::Random( int _min, int _max ) 
{
	return ( rand()%(_max - _min) ) + _min;
}
float SingleTon::Clamp( float _val, float _min, float _max ) 
{
	if( _val < _min ) return _min;
	if( _val > _max ) return _max;
	return _val;
}
CGPosition SingleTon::PointAdjustment( CGPosition _pos ) 
{
	_pos.x = Clamp( _pos.x, m_MoveRange.left, m_MoveRange.right );
	_pos.y = Clamp( _pos.y, m_MoveRange.top, m_MoveRange.bottom );
	return _pos;
}
CGPosition SingleTon::RandomPoint( CGPosition _pos, CGPosition _size )
{
	CGPosition pos;
	pos.x = ( rand()%((int)(_size.x - _pos.x)) ) + _pos.x;
	pos.y = ( rand()%((int)(_size.y - _pos.y)) ) + _pos.y;
	return pos;
}
bool SingleTon::PointExit( CGPosition pos )
{
	if( pos.x > m_MoveRange.left   &&
		pos.x < m_MoveRange.right  &&
		pos.y >= m_MoveRange.top   &&
		pos.y <= m_MoveRange.bottom ) return false;

	return true;
}

VectorInformation SingleTon::Distance( CGPosition _B, CGPosition _A )
{
	VectorInformation VI;
	VI.vec		= ccp	( _B.x - _A.x, _B.y - _A.y );
	VI.distance = sqrtf	( VI.vec.x * VI.vec.x + VI.vec.y * VI.vec.y );
	if( VI.distance ) {

		VI.vec.x	/= VI.distance;
		VI.vec.y	/= VI.distance;
	}

	return VI;
}

void SingleTon::CreateGDIOBJECT()
{
	pen[0] = CreatePen( PS_SOLID, 1, RGB(255,128,0) );
	pen[1] = CreatePen( PS_DASH , 1, RGB(255,128,0) );
	pen[2] = CreatePen( PS_SOLID, 1, RGB(0, 255, 0) );
	pen[3] = CreatePen( PS_SOLID, 1, RGB(0, 0, 255) );
	pen[4] = CreatePen( PS_NULL , 0, RGB( 0, 0, 0 ) );

	bru[0] = (HBRUSH)GetStockObject( NULL_BRUSH );
	bru[1] = CreateSolidBrush( RGB(0, 255, 0 )  );
	bru[2] = CreateSolidBrush( RGB(255, 0, 0 )  );
	bru[3] = CreateSolidBrush( RGB(20, 20, 20)  );
	bru[4] = CreateSolidBrush( RGB(0 , 0 , 0 )  );

	fnt[0] = CreateFont( 10, 0, 0, 0, 0, 0, 0, 0, HANGEUL_CHARSET, 0, 0, 0, 0, L"Arial" );
	SetBkColor	( m_hBackDC, RGB(0, 0, 0)		);
	SetBkMode	( m_hBackDC, TRANSPARENT		);
	SetTextColor( m_hBackDC, RGB(255, 128, 0)	);

	OriginPen	= (HPEN)  SelectObject( m_hBackDC, pen[0] );
	OriginBrush = (HBRUSH)SelectObject( m_hBackDC, bru[0] );
	OriginFont	= (HFONT) SelectObject( m_hBackDC, fnt[0] );
}
void SingleTon::ResetGDIOBJECT()
{
	SelectObject( m_hBackDC, OriginPen   );
	SelectObject( m_hBackDC, OriginBrush );
	SelectObject( m_hBackDC, OriginFont  );
}

void SingleTon::ChangePEN( int _Index ) 
{
	SelectObject( m_hBackDC, pen[_Index] );
}
void SingleTon::ChangeBRUSH( int _Index )
{
	SelectObject( m_hBackDC, bru[_Index] );
}
void SingleTon::ChangeFONT( int _Index )
{
	SelectObject( m_hBackDC, fnt[_Index] );
}

const TCHAR* SingleTon::IntToStateString( STATE _State )
{
	HDC	B = SingleTon::Call()->m_hBackDC;

	switch( _State )
	{
	case IDLE :
		SetTextColor( B, RGB(128, 255, 0) );
		return L"IDLE";
	case WALK :
		SetTextColor( B, RGB(255, 0, 128) );
		return L"WALK";
	case ATTACK :
		SetTextColor( B, RGB(0, 255, 128) );
		return L"ATTACK";
	case HIT :
		SetTextColor( B, RGB(0, 128, 255) );
		return L"HIT";
	}

	return L"FALSE";
}