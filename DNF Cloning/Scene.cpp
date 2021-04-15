#include "Scene.h"
#include "st.h"

void Scene::Init()
{
	memset(Obj_List, NULL, sizeof(Obj_List) );
}
void Scene::dealloc()
{
	for( int i = 0; i < MAX_OBJ; i++ ) {
		if( Obj_List[i] == NULL ) continue;

		Obj_List[i]->dealloc();
		delete Obj_List[i];
		Obj_List[i] = NULL;
	}
}
void Scene::run( float dt )
{
	for( int i = 0; i < MAX_OBJ; i++ ) {
		if( Obj_List[i] == NULL ) continue;
		if( !Obj_List[i]->GetActive() ) continue;

		Obj_List[i]->Update( dt );
		Obj_List[i]->Render();
	}

	InvalidateRect( SingleTon::Call()->m_hWnd, NULL, false );
}
void Scene::add_Obj( Object* _Obj ) 
{
	for( int i = 0; i < MAX_OBJ; i++ ) {
		if( Obj_List[i] != NULL ) continue;

		Obj_List[i] = _Obj;
		break;
	}
}
void Scene::add_Obj( Object* _Obj, OBJECTS _tag )
{
	_Obj->SetTag( _tag );
	this->add_Obj( _Obj );
}
Object* Scene::GetChildByTag( OBJECTS _tag )
{
	for( int i = 0; i < MAX_OBJ; i++ ) {
		if( Obj_List[i] == NULL ) continue;

		if( Obj_List[i]->GetTag() == _tag )
			return Obj_List[i];
	}

	return NULL;
}