#include "main.h"
#include "game.h"
#include "graphics.h"
#include "input.h"

FILE * the_log;

const char * program_name = "Fractal Racer";

void log(const char * szFormat, ...) {
	va_list arg_list;
	va_start(arg_list, szFormat);
	vfprintf(the_log, szFormat, arg_list);
	fflush(the_log);
	va_end(arg_list);
}

void Quit(int returnCode) {
	game_quit();
	log("\nIT'S OVER\n");
	fclose(the_log);											// close the log
    SDL_Quit();													// clean up the window
    exit(returnCode);											// and exit appropriately
}

int main ( int argc, char** argv ) {
	the_log = fopen("log.txt", "w");							// open the log
	uint SCREEN_WIDTH, SCREEN_HEIGHT;
	log(program_name);
	log("\n");
	for (int i = 0; i < argc; ++i)
		log("Program Argument: %s\n", argv[i]);

    int videoFlags;												// flags to pass to SDL_SetVideoMode
    const SDL_VideoInfo * videoInfo;							// holds some info about our display

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {							// initialize SDL
	    log("Video initialization failed: %s\n", SDL_GetError());
	    Quit(EXIT_FAILURE);
	}

    videoInfo = SDL_GetVideoInfo();								// Fetch the video info
    if (!videoInfo) {
	    log("Video query failed: %s\n", SDL_GetError());
	    Quit(EXIT_FAILURE);
	}

    SCREEN_WIDTH  = videoInfo->current_w;						// get the desktop's width
    SCREEN_HEIGHT = videoInfo->current_h;						// get the desktop's height
    log("Screen Resolution: %d x %d\n", SCREEN_WIDTH, SCREEN_HEIGHT);

	videoFlags  = SDL_OPENGL;									// Enable OpenGL in SDL
	videoFlags |= SDL_GL_DOUBLEBUFFER;							// Enable double buffering
	videoFlags |= SDL_HWPALETTE;     							// Store the palette in hardware
	videoFlags |= SDL_RESIZABLE;      							// Enable window resizing
	videoFlags |= SDL_FULLSCREEN;      							// Enable full screen mode

    if (videoInfo->hw_available)								// Check to see if surfaces can be stored in memory
		videoFlags |= SDL_HWSURFACE;
    else
		videoFlags |= SDL_SWSURFACE;

    if (videoInfo->blit_hw)										// Checks if hardware blits can be done
		videoFlags |= SDL_HWACCEL;

    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);				// Sets up OpenGL double buffering

	SDL_Surface * surface = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 0, videoFlags);
    if (!surface) {												// verify the creation of the surface
	    log("Video mode set failed: %s\n", SDL_GetError());
	    Quit(EXIT_FAILURE);
	}
	SDL_WM_SetCaption(program_name, NULL );
	SDL_ShowCursor(false);
	SDL_WM_GrabInput(SDL_GRAB_ON);

    if (!graphics_init(SCREEN_WIDTH, SCREEN_HEIGHT)) {			// initialize OpenGL
	    log("Failed to initialize graphics.\n");
	    Quit(EXIT_FAILURE);
    }

	game_init();
	build_key_map();
	build_mouse_map();

    while (process_events()) {
		static uint then = 0;
		uint now = SDL_GetTicks();
		uint dt = now - then;
		step(dt);
		render(surface, dt);
	   	then = now;
	}
    Quit(EXIT_SUCCESS);
    return EXIT_SUCCESS;
}
