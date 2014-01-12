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
short INPUT::mouse_dx = 0;
short INPUT::mouse_dy = 0;
bool INPUT::mouse_moved = false;
bool INPUT::warping = false;

unsigned int INPUT::quit_key = 0;

void INPUT::move_mouse( short x, short y ) {
	if( warping ) {
		warping = false;
		return;
	}
	last_mouse_x = mouse_x;
	last_mouse_y = mouse_y;
	mouse_x = x;
	mouse_y = y;
	mouse_dx = mouse_x - last_mouse_x;
	mouse_dy = mouse_y - last_mouse_y;
	mouse_moved = true;
}

void INPUT::poll_mouse( bool force_warp ) {
	if( force_warp || mouse_x < 100 || mouse_x > GLOBAL::window_width-100 || mouse_y < 100 || mouse_y > GLOBAL::window_height-100 ) {
		warping = true;
		mouse_x = GLOBAL::window_width/2;
		mouse_y = GLOBAL::window_height/2;
		glutWarpPointer( GLOBAL::window_width/2, GLOBAL::window_height/2 );
	}
	last_mouse_x = mouse_x;
	last_mouse_y = mouse_y;
	mouse_dx = mouse_dy = 0;
	mouse_moved = false;
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
