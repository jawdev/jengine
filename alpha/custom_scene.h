/*******************************************************
 * Created by JAW Development
 * jawdev > jengine > custom_scene.h
*******************************************************/

///////////////////////////////////////////////// CustomScene

class CustomScene : public jengine::Scene {
public:
	CustomScene();

	void load();
	void unload();
	void reshape();
	void display();
private:
	jengine::Renderbuffer* m_pRenderbuffer;
};
