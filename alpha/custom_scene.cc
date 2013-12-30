/*******************************************************
 * Created by JAW Development
 * jawdev > jengine > custom_scene.cc
*******************************************************/
#include "custom_config.h"

///////////////////////////////////////////////// CustomScene

CustomScene::CustomScene() : jengine::Scene( "custom" ) {
	m_pShaderProgram = nullptr;
}

void CustomScene::load() {
	chrono::high_resolution_clock::time_point t1 = chrono::high_resolution_clock::now();

	m_pShaderProgram = new jengine::ShaderProgram();
	m_pShaderProgram->add_shader( GL_VERTEX_SHADER, "resources/shaders/default.vs" );
	m_pShaderProgram->add_shader( GL_FRAGMENT_SHADER, "resources/shaders/default.fs" );
	m_pShaderProgram->link();
	m_pShaderProgram->use();
	m_pShaderProgram->spec( *( new jengine::ShaderSpecRef ) );

	chrono::high_resolution_clock::time_point t2 = chrono::high_resolution_clock::now();
	float diff = float( chrono::duration_cast< chrono::duration< float > >( t2-t1 ).count() );
	cout << "time: " << setprecision( 16 ) <<  setiosflags( ios::fixed|ios::showpoint ) << diff << endl;

}

void CustomScene::unload() {
	delete m_pRenderbuffer;
	delete m_pShaderProgram;
}

