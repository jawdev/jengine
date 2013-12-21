/*******************************************************
 * Created by JAW Development
 * jawdev > jengine > custom_scene.cc
*******************************************************/
#include "custom_config.h"

///////////////////////////////////////////////// CustomScene

CustomScene::CustomScene() : jengine::Scene( "custom" ) {
	
}

void CustomScene::load() {
	cout << "Loading custom scene" << endl;
	m_pRenderbuffer = new jengine::Renderbuffer();
}

void CustomScene::unload() {
	cout << "Unloading custom scene" << endl;
	delete m_pRenderbuffer;
}

void CustomScene::reshape() {
	cout << "Reshaping custom scene" << endl;
	m_pRenderbuffer->resize();
}

void CustomScene::display() {
	cout << "Displaying custom scene" << endl;
	m_pRenderbuffer->use();
	Scene::update_filters();
	m_pRenderbuffer->blit();
}
