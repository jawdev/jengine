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
	timer* pTimer = new timer();

	m_pShaderProgram = new ShaderProgram();
	m_pShaderProgram->add_shader( GL_VERTEX_SHADER, "resources/shaders/default.vs" );
	m_pShaderProgram->add_shader( GL_FRAGMENT_SHADER, "resources/shaders/default.fs" );
	m_pShaderProgram->link();
	m_pShaderProgram->spec( *( new ShaderSpecRef ) );
	m_pShaderProgram->use();

	InputMap* pIM = new InputMap();
	pIM->multiply_transform( 2, 20 );
	Scene::camera()->map_input( pIM );
	Scene::camera()->position( vec( 1, 1, 4 ) );
	Scene::camera()->look_at( vec() );

	Box* pObj1 = new Box( 1, vec( 0, 0, 1 ) );
	pObj1->spin( vec( 0, 1 ) );

	Filter* pF = new Filter();
	pF->add( pObj1 );
	Scene::push_filter( pF );

	// OpenGL settings
	glEnable( GL_CULL_FACE );

	cout << "-----------------------" << endl;
	cout << "|  time: " << pTimer->calculate_delta() << "  |" << endl;
	cout << "-----------------------" << endl;
	delete pTimer;
}

void CustomScene::unload() {
	SAFE_DELETE( m_pShaderProgram );
}
