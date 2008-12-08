#ifndef GRAPHICS_H_INCLUDED
#define GRAPHICS_H_INCLUDED

#include "main.h"
#include "track.h"

void reshape(uint, uint);

bool graphics_init(uint, uint);

void switch_view_mode(uint);

void render(SDL_Surface * screen, uint dt);

#endif // GRAPHICS_H_INCLUDED
