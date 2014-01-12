/*******************************************************
 * Created by JAW Development
 * jawdev > jengine > custom_scene.cc
*******************************************************/
#include "custom_config.h"

///////////////////////////////////////////////// CustomScene

CustomScene::CustomScene() : Scene( "custom" ) {
	m_pShaderProgram = nullptr;
	Scene::disable( SCENE_RENDERBUFFER );
}

void CustomScene::load() {
	chrono::high_resolution_clock::time_point t1 = chrono::high_resolution_clock::now();

	m_pShaderProgram = new ShaderProgram();
	m_pShaderProgram->add_shader( GL_VERTEX_SHADER, "resources/shaders/default.vs" );
	m_pShaderProgram->add_shader( GL_FRAGMENT_SHADER, "resources/shaders/default.fs" );
	m_pShaderProgram->link();
	m_pShaderProgram->spec( *( new ShaderSpecRef ) );
	m_pShaderProgram->use();

	//Scene::camera()->project( PROJ_NONE );
	Scene::camera()->position( vec( 2, 1, 2 ) );
	Scene::camera()->velocity( vec( -0.4f ) );
	

	Filter* pF = new Filter();
	FloorPlane* pFloor = new FloorPlane( 1, 1 );
	pF->add( pFloor );
	Scene::push_filter( pF );

	chrono::high_resolution_clock::time_point t2 = chrono::high_resolution_clock::now();
	float diff = float( chrono::duration_cast< chrono::duration< float > >( t2-t1 ).count() );
	cout << "time: " << setprecision( 16 ) <<  setiosflags( ios::fixed|ios::showpoint ) << diff << endl;

}

void CustomScene::unload() {
	SAFE_DELETE( m_pShaderProgram );
}
