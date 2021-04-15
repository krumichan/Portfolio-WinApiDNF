#include "Scene_Title.h"
#include "Scene_Tower.h"
#include "st.h"

Scene_Title* Scene_Title::scene()
{
	Scene_Title *p = new Scene_Title;
	p->Init();
	return p;
}
void Scene_Title::Init() 
{
	Scene::Init();
}
void Scene_Title::run( float dt )
{
	Scene::run( dt );

	TextOut(SingleTon::Call()->m_hBackDC, 700, 300, L"Push SpaceBar!!" , _tcslen(L"Push SpaceBar!!"));

	if( GetAsyncKeyState(VK_SPACE) ) {
		SingleTon::Call()->replaceScene( Scene_Tower::scene() );
	}
	else if( !GetAsyncKeyState(VK_SPACE) ) {

	}
}