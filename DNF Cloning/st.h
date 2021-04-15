#pragma once
#include "Header.h"
#include "SoundManager.h"
#include "BulletManager.h"
#include "EnemyManager.h"
#include "EffectManager.h"
#include "Scene.h"

class SingleTon {

private:
	SingleTon();
public:
	static	SingleTon*		Instance;
	static	SingleTon*		Call();
	
			HDC				m_hBackDC;
			HDC				m_hMemDC;
			HBITMAP			m_hBackBMP;
			HINSTANCE		m_Instance;
			HWND			m_hWnd;

			void			CreateBackBuffer( HWND hWnd		);
			void			dealloc			(				);
			HBITMAP			GetBMP			( int _Index	);

			SoundManager	SM;
			BulletManager	BM;
			EnemyManager	EM;
			EffectManager	EfM;

			Scene*			m_pNowRunningScene;
			void			replaceScene	( Scene* _scene );

			RECT			m_MoveRange;

			int				Random			( int _min, int _max				);
			float			Clamp			( float _val, float _min, float _max	);
			CGPosition		PointAdjustment	( CGPosition _pos					);
			CGPosition		RandomPoint		( CGPosition _pos, CGPosition _size );
			bool			PointExit		( CGPosition pos					);
			VectorInformation Distance		( CGPosition _B, CGPosition _A		);

			HPEN			pen[5];
			HBRUSH			bru[5];
			HFONT			fnt[1];
			HPEN			OriginPen;
			HBRUSH			OriginBrush;
			HFONT			OriginFont;

			void			CreateGDIOBJECT	(				);
			void			ResetGDIOBJECT	(				);
			void			ChangePEN		( int   _Index	);
			void			ChangeBRUSH		( int   _Index	);
			void			ChangeFONT		( int   _Index	);
	const	TCHAR*			IntToStateString( STATE _iState	);
};