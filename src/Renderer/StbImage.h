#ifndef STBIMAGE
#define STBIMAGE

#include <cstdlib>
#include <string>
#include <iostream>
#include <vector>
using namespace std;

#include "GL/glew.h"
#include "glm/glm.hpp"

class StbImage
{
public:
	StbImage(string name);
	
	vector<unsigned char> getPixels();
	glm::ivec2 getSize();
	
	void flipY();
	glm::vec4 getRgba(glm::ivec2 position);

private:
	vector<unsigned char> pixels_;
	glm::ivec2 size_;
	int channels_;
};

#endif