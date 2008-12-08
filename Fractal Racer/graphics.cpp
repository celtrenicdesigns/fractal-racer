#include "graphics.h"

#define DRAW_DISTANCE      256.f

GLfloat x_rot = 0.f, y_rot = 180.f;
GLfloat x_pos = 0.f, y_pos = 3.f, z_pos = -20.f;

extern Track * track;

void reshape(uint width, uint height) {							// This function is called when our window is resized
	if (height == 0)											// Prevent A Divide By Zero If The Window Is Too Small
		height = 1;

	glViewport(0, 0, width, height);							// Reset The Current Viewport And Perspective Transformation
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0f, (GLfloat)width / (GLfloat)height, 0.5f, DRAW_DISTANCE);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

bool graphics_init(uint SCREEN_WIDTH, uint SCREEN_HEIGHT) {
	glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);				// Set the Viewport
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);			// Realy Nice perspective calculations
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);						// Light Grey Background
	glClearDepth(1.0f);											// Depth Buffer Setup
	glShadeModel(GL_SMOOTH);									// Enables Smooth Color Shading
	glEnable(GL_DEPTH_TEST);									// Enable Depth Testing
	glDepthFunc(GL_LEQUAL);										// The Type Of Depth Testing (Less Or Equal)
	glDisable(GL_LINE_SMOOTH);									// Disable Line Smoothing
	glEnable(GL_CULL_FACE);										// Enable OpenGL Face Culling
	glCullFace(GL_BACK);										// Cull Back Facing Polygons
	//glEnable(GL_TEXTURE_2D);									// Enable Texture Mapping
	glEnable(GL_LIGHTING);										// Enable OpenGL Lighting


	GLfloat mat_ambient[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat mat_diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse );
	glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient );

	// Set light 0 to be a simple, bright directional light to use
    // on the mesh that will represent light 2
	GLfloat diffuse_light0[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat position_light0[] = { 0.5f, -0.5f, -0.5f, 0.0f };
	glLightfv( GL_LIGHT0, GL_DIFFUSE, diffuse_light0 );
	glLightfv( GL_LIGHT0, GL_POSITION, position_light0 );

	// Set light 1 to be a simple, faint grey directional light so
    // the walls and floor are slightly different shades of grey
	GLfloat diffuse_light1[] = { 0.25f, 0.25f, 0.25f, 1.0f };
	GLfloat position_light1[] = { 0.3f, -0.5f, 0.2f, 0.0f };
	//GLfloat position_light1[] = { 0.3f, -0.5f, -0.2f, 0.0f };
	glLightfv( GL_LIGHT1, GL_DIFFUSE, diffuse_light1 );
	glLightfv( GL_LIGHT1, GL_POSITION, position_light1 );

	// Light #2 will be the demo light used to light the floor and walls.
	// It will be set up in render() since its type can be changed at
    // run-time.

	// Enable some dim, grey ambient lighting so objects that are not lit
    // by the other lights are not completely black.
	GLfloat ambient_lightModel[] = { 0.25f, 0.25f, 0.25f, 1.0f };
	glLightModelfv( GL_LIGHT_MODEL_AMBIENT, ambient_lightModel );


    reshape(SCREEN_WIDTH, SCREEN_HEIGHT);
	return true;
}

void switch_view_mode(uint key_state) {
	if (key_state == SDL_KEYUP) {
		static bool view_mode = true;
		if (view_mode)
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);			// Wireframe mode
		else
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);			// Mesh mode
		view_mode = !view_mode;
	}
}

void draw_cube(GLfloat size) {
	glBegin(GL_QUADS); {
		glColor3f(0.0f,size,0.0f);				// Set The Color To Green
		glVertex3f( size, size,-size);			// Top Right Of The Quad (Top)
		glVertex3f(-size, size,-size);			// Top Left Of The Quad (Top)
		glVertex3f(-size, size, size);			// Bottom Left Of The Quad (Top)
		glVertex3f( size, size, size);			// Bottom Right Of The Quad (Top)

		glColor3f(size,0.5f,0.0f);				// Set The Color To Orange
		glVertex3f( size,-size, size);			// Top Right Of The Quad (Bottom)
		glVertex3f(-size,-size, size);			// Top Left Of The Quad (Bottom)
		glVertex3f(-size,-size,-size);			// Bottom Left Of The Quad (Bottom)
		glVertex3f( size,-size,-size);			// Bottom Right Of The Quad (Bottom)

		glColor3f(size,0.0f,0.0f);				// Set The Color To Red
		glVertex3f( size, size, size);			// Top Right Of The Quad (Front)
		glVertex3f(-size, size, size);			// Top Left Of The Quad (Front)
		glVertex3f(-size,-size, size);			// Bottom Left Of The Quad (Front)
		glVertex3f( size,-size, size);			// Bottom Right Of The Quad (Front)

		glColor3f(size,size,0.0f);				// Set The Color To Yellow
		glVertex3f( size,-size,-size);			// Bottom Left Of The Quad (Back)
		glVertex3f(-size,-size,-size);			// Bottom Right Of The Quad (Back)
		glVertex3f(-size, size,-size);			// Top Right Of The Quad (Back)
		glVertex3f( size, size,-size);			// Top Left Of The Quad (Back)

		glColor3f(0.0f,0.0f,size);				// Set The Color To Blue
		glVertex3f(-size, size, size);			// Top Right Of The Quad (Left)
		glVertex3f(-size, size,-size);			// Top Left Of The Quad (Left)
		glVertex3f(-size,-size,-size);			// Bottom Left Of The Quad (Left)
		glVertex3f(-size,-size, size);			// Bottom Right Of The Quad (Left)

		glColor3f(size,0.0f,size);				// Set The Color To Violet
		glVertex3f( size, size,-size);			// Top Right Of The Quad (Right)
		glVertex3f( size, size, size);			// Top Left Of The Quad (Right)
		glVertex3f( size,-size, size);			// Bottom Left Of The Quad (Right)
		glVertex3f( size,-size,-size);			// Bottom Right Of The Quad (Right)
	} glEnd();
}

GLfloat cube_diffuse[4] = { 0.5f, 0.5f, 1.f, 1.f };
GLfloat cube_ambient[4] = { 0.f, 0.f, 1.f, 1.f };
GLfloat cube_emission[4] = { 0.1f, 0.1f, 0.2f, 1.f };
GLfloat cube_specular[4] = { 1.f, 1.f, 1.f, 1.f };
GLfloat cube_shininess = 5;

void render(SDL_Surface * screen, uint dt) {
	if (SDL_MUSTLOCK(screen)) {
		if (SDL_LockSurface(screen) < 0) {
			log("Could not get a screen lock.\n");
			return;
		}
	}

	static double elapsed_time = 0;
	elapsed_time += (double)dt / 10.f;
	while (elapsed_time > track->length())
		elapsed_time -= track->length();

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	//glTranslatef(x_pos, -y_pos, z_pos);
	float x = track->x_pos(elapsed_time);
	float z = elapsed_time;
	glTranslatef(track->x_pos(elapsed_time - 15), -y_pos, z - 20);
	glRotatef(x_rot, 1.0f, 0.0f, 0.0f);
	glRotatef(y_rot, 0.0f, 1.0f, 0.0f);

	//Lighting stuff
	GLfloat diffuse_light2[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat position_light2[] = { x, 1.f, z, 1.0f };
	GLfloat linearAttenuation_light2[] = { 0.4f };
	glLightfv( GL_LIGHT2, GL_DIFFUSE, diffuse_light2 );
	glLightfv( GL_LIGHT2, GL_POSITION, position_light2 );
	glLightfv( GL_LIGHT2, GL_LINEAR_ATTENUATION , linearAttenuation_light2 );

    glEnable( GL_LIGHT0 );
    glDisable( GL_LIGHT1 );
    glDisable( GL_LIGHT2 );

	glPushMatrix(); {
		glLoadIdentity();

		GLfloat pPosition_light2[4];
		glGetLightfv( GL_LIGHT2, GL_POSITION, pPosition_light2 );
		glTranslatef( pPosition_light2[0], pPosition_light2[1], pPosition_light2[2] );

		glMaterialfv( GL_FRONT_AND_BACK, GL_DIFFUSE, cube_diffuse );
		glMaterialfv( GL_FRONT_AND_BACK, GL_AMBIENT, cube_ambient );
		glMaterialfv( GL_FRONT_AND_BACK, GL_EMISSION, cube_emission );
		glMaterialfv( GL_FRONT_AND_BACK, GL_SPECULAR, cube_specular );
		glMaterialf( GL_FRONT_AND_BACK, GL_SHININESS, cube_shininess );

		draw_cube(0.1f);
	} glPopMatrix();

    glDisable( GL_LIGHT0 );
    glEnable( GL_LIGHT1 );
    glEnable( GL_LIGHT2 );

	//TODO insert code here

	track->render();

	//TODO insert code here

	SDL_GL_SwapBuffers();
	if (SDL_MUSTLOCK(screen)) {
		SDL_UnlockSurface(screen);
	}
}
