/*******************************************************
 * Created by JAW Development
 * jawdev > jengine > main.cc
*******************************************************/

#include "custom_config.h"

int main( int argc, char* argv[] ) {

	jengine::SETUP setup;
	setup.argc = &argc;
	setup.argv = argv;
	setup.window_title = "Test Game | JEngine";
	jengine::JEngine je( setup );

	je.start();
	return 0;
}


