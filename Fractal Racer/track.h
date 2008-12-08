#ifndef TRACK_H_INCLUDED
#define TRACK_H_INCLUDED

#include "main.h"

struct point {
	float x, y, z;
	point() : x(0.f), y(0.f), z(0.f) {};
	point(float x, float y, float z) : x(x), y(y), z(z) {};
};

class Track {
	public:
		Track(uint difficulty, double length);
		~Track();

		void render();

		float x_pos(float z);

		inline uint points() { return num_cps; }
		inline double length() { return len; }

	private:
		uint num_cps;
		double len;
		point * control_points;
};

#endif // TRACK_H_INCLUDED
