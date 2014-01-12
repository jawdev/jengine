/*******************************************************
 * Created by JAW Development
 * jawdev > jengine > custom_scene.h
*******************************************************/

using namespace jengine;

///////////////////////////////////////////////// CustomScene

class CustomScene : public Scene {
public:
	CustomScene();

	void load();
	void unload();

	//void render();
private:
	ShaderProgram* m_pShaderProgram;
	GLuint m_VA;
	GLuint m_VB;
};
