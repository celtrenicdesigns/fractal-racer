#include "game.h"

enum STATE { RACING, NOT_RACING } game_state;

Track * track;

void game_init() {
	game_state = NOT_RACING;
	track = new Track(10, 1024);
	//TODO build first track
	log("Game init completed.\n");
}

void game_quit() {
	delete track;
}

void step(uint dt) {
	//TODO insert code here
}
