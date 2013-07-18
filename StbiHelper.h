#ifndef STBIHELPER
#define STBIHELPER

#include <cstdlib>
#include <iostream>
using namespace std;

#include "GL/glew.h"
#include "glm/glm.hpp"

class StbiHelper
{
public:
	static glm::vec4 getRgba(unsigned char *pixels, int width, int height, int channels, unsigned int x, unsigned int y);
	static unsigned char *flipY(unsigned char *pixels, int width, int height, int channels);

private:
};

#endif