#include "Scene_Tower.h"
#include "Obj_BGA.h"
#include "Obj_Hero.h"
#include "BulletManager.h"
#include "st.h"

Scene_Tower* Scene_Tower::scene()
{
	Scene_Tower *p = new Scene_Tower;
	p->Init();
	return p;
}
void Scene_Tower::Init()
{
	Scene::Init  ( );
	this->add_Obj( Object_Background::Create() );
	this->add_Obj( Object_Hero::Create(), HERO );

	RECT Ran;
	Ran.left	= 0;
	Ran.right	= 1430;
	Ran.top		= 337;
	Ran.bottom	= 568;

	SingleTon::Call()->m_MoveRange = Ran;
	SingleTon::Call()->EM.Init ( this );
	SingleTon::Call()->BM.Init ( this );
	SingleTon::Call()->EfM.Init( this );

	for( int i = 0; i < 16; i++ ) {
		float _X = SingleTon::Call()->Random( Ran.left, Ran.right );
		float _Y = SingleTon::Call()->Random( Ran.top, Ran.bottom );
		SingleTon::Call()->EM.addEnemy( ccp(_X, _Y) );
	}
	SingleTon::Call()->SM.play( SND_BGM );
}

void Scene_Tower::run( float dt )
{
	Scene::run( dt );
	SingleTon::Call()->BM.UseRateDisplay( ccp(10, 15) );
	SingleTon::Call()->EM.UseRateDisplay( ccp(10, 30) );
}