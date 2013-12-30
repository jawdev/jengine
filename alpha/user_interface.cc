/*******************************************************
 * Created by JAW Development
 * jawdev > jengine > user_interface.cc
*******************************************************/
#include "jengine.h"
namespace jengine {

///////////////////////////////////////////////// INPUT

bool INPUT::key[256] = { false };
bool INPUT::special[256] = { false };
bool INPUT::mouse[10] = { false };

int INPUT::key_down = -1;
int INPUT::key_up = -1;
int INPUT::special_down = -1;
int INPUT::special_up = -1;
int INPUT::mouse_down = -1;
int INPUT::mouse_up = -1;

short INPUT::mouse_x = 0;
short INPUT::mouse_y = 0;
short INPUT::last_mouse_x = 0;
short INPUT::last_mouse_y = 0;

unsigned int INPUT::quit_key = 0;

void INPUT::move_mouse( short x, short y ) {
	last_mouse_x = mouse_x;
	last_mouse_y = mouse_y;
	mouse_x = x;
	mouse_y = y;
}

void INPUT::reset_events() {
	key_down = -1;
	key_up = -1;
	special_down = -1;
	special_up = -1;
	mouse_down = -1;
	mouse_up = -1;
}

} //jengine
