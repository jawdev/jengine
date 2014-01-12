/*******************************************************
 * Created by JAW Development
 * jawdev > jengine > main.cc
*******************************************************/

#include "custom_config.h"

int main( int argc, char* argv[] ) {

	SETUP setup;
	setup.argc = &argc;
	setup.argv = argv;
	setup.window_title = "Test Game | JEngine";
	setup.quit_key = 27;
	JEngine je( setup );
 
	je.load_scene( new CustomScene );
	je.start();

	return 0;
}


