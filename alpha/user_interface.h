/*******************************************************
 * Created by JAW Development
 * jawdev > jengine > user_interface.h
*******************************************************/
#ifndef __JENGINE_USER_INTERFACE_H__
#define __JENGINE_USER_INTERFACE_H__
namespace jengine {

///////////////////////////////////////////////// KEYBOARD

struct INPUT {
	
	static const unsigned int MOUSE_LEFT = 0;
	static const unsigned int MOUSE_MIDDLE = 1;
	static const unsigned int MOUSE_RIGHT = 2;

	static bool key[256];
	static bool special[256];
	static bool mouse[10];

	static int key_down;
	static int key_up;
	static int special_down;
	static int special_up;
	static int mouse_down;
	static int mouse_up;

	static short mouse_x;
	static short mouse_y;
	static short last_mouse_x;
	static short last_mouse_y;

	static void move_mouse( short x, short y );
	static void reset_events();
};


} //jengine
#endif //__JENGINE_USER_INTERFACE_H__
