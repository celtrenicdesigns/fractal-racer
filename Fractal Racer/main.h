#ifndef MAIN_H_INCLUDED
#define MAIN_H_INCLUDED

#ifdef __cplusplus
#	include <cstdlib>
#	include <cstdio>
#	include <cstdarg>
#	include <ctime>
#else
#	include <stdlib.h>
#	include <stdio.h>
#	include <stdarg.h>
#	include <time.h>
#endif

#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <math.h>
#include <map>
#include <vector>

using namespace std;

typedef unsigned int  uint;
typedef unsigned char uchar;

void log(const char *, ...);

//#define log printf

#endif // MAIN_H_INCLUDED
