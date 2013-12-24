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
	m_pRenderbuffer = new jengine::Renderbuffer();

	m_pShaderProgram = new jengine::ShaderProgram();
	m_pShaderProgram->add_shader( GL_VERTEX_SHADER, "resources/shaders/default.vs" );
	m_pShaderProgram->add_shader( GL_FRAGMENT_SHADER, "resources/shaders/default.fs" );
	m_pShaderProgram->link();
	m_pShaderProgram->use();
	m_pShaderProgram->spec( *( new jengine::ShaderSpecRef ) );

	cout << jengine::GLOBAL::shader_spec[jengine::ULOC_CAMERA_MAT] << endl;
}

void CustomScene::unload() {
	delete m_pRenderbuffer;
	delete m_pShaderProgram;
}

void CustomScene::display() {
	m_pRenderbuffer->use();
	Scene::update_filters();
	m_pRenderbuffer->blit();
}
