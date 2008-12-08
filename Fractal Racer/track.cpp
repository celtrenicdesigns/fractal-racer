#include "track.h"

GLfloat floor_diffuse[4] = { 1.f, 0.f, 0.f, 1.f };
GLfloat floor_ambient[4] = { 1.f, 0.f, 0.f, 1.f };
GLfloat floor_emission[4] = { 0.2f, 0.1f, 0.1f, 1.f };
GLfloat floor_specular[4] = { 1.f, 1.f, 1.f, 1.f };
GLfloat floor_shininess = 5.f;

GLfloat wall_diffuse[4] = { 0.f, 1.f, 0.f, 1.f };
GLfloat wall_ambient[4] = { 0.f, 1.f, 0.f, 1.f };
GLfloat wall_emission[4] = { 0.2f, 0.2f, 0.1f, 1.f };
GLfloat wall_specular[4] = { 1.f, 1.f, 1.f, 1.f };
GLfloat wall_shininess = 5.f;

Track::Track(uint difficulty, double length) : len(length) {
	srand(time(NULL));
	uint n = (1 << difficulty) + 1;
	control_points = new point[n];
	num_cps = n--;
	uint i, b;
	control_points[0] = point(0.f, 0.f, 0.f);
	control_points[n] = point(4 * sinf(n/32.f), 0.f, len);
	for (b = 2; b <= n; b = b << 1) {
		for (i = n/b; i < n; i += n / (b >> 1)) {
			control_points[i] = point(4 * sinf(i/32.f), 0.f, len * i / n);
		}
	}
}

Track::~Track() {
	delete [] control_points;
}

void Track::render() {
	glMaterialfv( GL_FRONT_AND_BACK, GL_DIFFUSE, floor_diffuse );
	glMaterialfv( GL_FRONT_AND_BACK, GL_AMBIENT, floor_ambient );
	glMaterialfv( GL_FRONT_AND_BACK, GL_EMISSION, floor_emission );
	glMaterialfv( GL_FRONT_AND_BACK, GL_SPECULAR, floor_specular );
	glMaterialf( GL_FRONT_AND_BACK, GL_SHININESS, floor_shininess );
	for (int j = -5; j < 5; j += 2) {
		glBegin(GL_QUAD_STRIP); {
			for (uint i = 0; i < num_cps; ++i) {
				glVertex3f(control_points[i].x + j + 2.f, control_points[i].y, control_points[i].z);
				glVertex3f(control_points[i].x + j, control_points[i].y, control_points[i].z);
			}
		} glEnd();
	}

	glMaterialfv( GL_FRONT_AND_BACK, GL_DIFFUSE, wall_diffuse );
	glMaterialfv( GL_FRONT_AND_BACK, GL_AMBIENT, wall_ambient );
	glMaterialfv( GL_FRONT_AND_BACK, GL_EMISSION, wall_emission );
	glMaterialfv( GL_FRONT_AND_BACK, GL_SPECULAR, wall_specular );
	glMaterialf( GL_FRONT_AND_BACK, GL_SHININESS, wall_shininess );
	for (int j = 0; j < 3; ++j) {
		glBegin(GL_QUAD_STRIP); {
			for (uint i = 0; i < num_cps; ++i) {
				glVertex3f(control_points[i].x - 5.f - j, control_points[i].y + j, control_points[i].z);
				glVertex3f(control_points[i].x - 5.f - j - 1.f, control_points[i].y + j + 1.f, control_points[i].z);
			}
		} glEnd();
	}
	for (int j = 0; j < 3; ++j) {
		glBegin(GL_QUAD_STRIP); {
			for (uint i = 0; i < num_cps; ++i) {
				glVertex3f(control_points[i].x + 5.f + j + 1.f, control_points[i].y + j + 1.f, control_points[i].z);
				glVertex3f(control_points[i].x + 5.f + j, control_points[i].y + j, control_points[i].z);
			}
		} glEnd();
	}
}

/**
 * TODO: Replace with cubic interpolation!
 */
float Track::x_pos(float z) {
	if (z < 0 || z > len)
		return 0;
	else
		return control_points[(uint)(num_cps * z / len)].x;
}
