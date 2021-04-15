#include "Header.h"
#include "Scene_Title.h"

#include "st.h"
SingleTon* SingleTon::Instance = NULL;

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR strCmdLine, int nShowCmd)
{
	WNDCLASSEX wcex;
	memset(&wcex, 0, sizeof(wcex));

	wcex.cbSize				= sizeof(wcex);
	wcex.style				= CS_HREDRAW | CS_VREDRAW;
	wcex.hbrBackground		= (HBRUSH)GetStockObject(WHITE_BRUSH);
	wcex.hCursor			= LoadCursor(NULL, IDC_ARROW);
	wcex.hIcon				= LoadIcon(NULL, IDI_APPLICATION);
	wcex.hInstance			= hInstance;
	wcex.cbClsExtra			= 0;
	wcex.cbWndExtra			= 0;
	wcex.hIconSm			= NULL;
	wcex.lpszMenuName		= NULL;
	wcex.lpfnWndProc		= WndProc;
	wcex.lpszClassName		= L"MyWindow";
	RegisterClassEx(&wcex);
	
	HWND hWnd = CreateWindow(L"MyWindow", L"MyWindow", WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, 1440, 600, NULL, NULL, hInstance, NULL);

	if (hWnd == NULL)
	{
		MessageBox(NULL, L"윈도우 생성 실패", L"에러", MB_ICONERROR | MB_OK);
		return -1;
	}

	ShowWindow(hWnd, SW_SHOW);

	SingleTon::Call()->replaceScene( Scene_Title::scene() );

	MSG		msg; 
	memset(&msg, 0, sizeof(msg));

	int		iFlag	= 1;
	DWORD	dt		= timeGetTime();
	DWORD	et		= timeGetTime();

	while ( iFlag )
	{
		dt = timeGetTime() - et;
		et = timeGetTime();
		float FDT = dt / 1000.f;

		if( SingleTon::Call()->m_pNowRunningScene )
			SingleTon::Call()->m_pNowRunningScene->run( FDT );

		if ( PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) ) {
			if (msg.message == WM_QUIT)
				iFlag = 0;

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
	SingleTon::Call()->m_pNowRunningScene->dealloc();
	delete SingleTon::Call()->m_pNowRunningScene;

	return 0;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_CREATE:
		{
			SingleTon::Call()->CreateBackBuffer( hWnd );
			SingleTon::Call()->SM.Init();
			SingleTon::Call()->SM.loading();
			break;

		}
	case WM_DESTROY:
		{
			SingleTon::Call()->dealloc();
			PostQuitMessage(0);
			break;
		}
	case WM_PAINT:
		{
			PAINTSTRUCT ps;
			HDC hDC = BeginPaint(hWnd, &ps);
			BitBlt(hDC, 0, 0, 1440, 600, SingleTon::Call()->m_hBackDC, 0, 0, SRCCOPY);
			EndPaint(hWnd, &ps);
			break;

		}
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}