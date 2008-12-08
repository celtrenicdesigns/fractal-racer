#include "input.h"

map<SDLKey, void (*)(uint)> key_map;
map<uint,   void (*)()>     mouse_map;

//TODO read keymap from file
void build_key_map() {
	/*
	key_map[SDLK_w] = &move_forward;
	key_map[SDLK_s] = &move_backward;
	key_map[SDLK_a] = &turn_left;
	key_map[SDLK_d] = &turn_right;
	key_map[SDLK_r] = &run;
	key_map[SDLK_SPACE] = &jump;
	*/
	key_map[SDLK_F9] = &switch_view_mode;
}

void build_mouse_map() {
	/*
	mouse_map[1] = &use;		//left click
	mouse_map[4] = &zoom_in;	//mouse wheel up
	mouse_map[5] = &zoom_out;	//mouse wheel down
	*/
}

bool process_events() {
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		switch (event.type) {
			case SDL_QUIT: {
				return false;
			}
			case SDL_KEYDOWN: {
				SDLKey sym = event.key.keysym.sym;

				if(sym == SDLK_ESCAPE)
					return false;
				else if (key_map.find(sym) != key_map.end())
					(*key_map[sym])(SDL_KEYDOWN);
				break;
			}
			case SDL_KEYUP: {
				SDLKey sym = event.key.keysym.sym;

				if (key_map.find(sym) != key_map.end())
					(*key_map[sym])(SDL_KEYUP);
				break;
			}
			case SDL_MOUSEBUTTONDOWN: {
				uint button = event.button.button;
				if (mouse_map.find(button) != mouse_map.end())
					(*mouse_map[button])();
				break;
			}
			case SDL_MOUSEMOTION: {
				//SDL_MouseMotionEvent motion = event.motion;
				//mouse_move(motion.xrel, motion.yrel);
				break;
			}
			default:
				break;
		}
	}
	return true;
}
