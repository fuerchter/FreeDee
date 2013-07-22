#ifndef SHAPE
#define SHAPE

#include <vector>
#include <string>
#include <iostream>
using namespace std;

#include "GL/glew.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "tiny_obj_loader.h"

#include "Drawable.h"
#include "StbImage.h"

class Shape : Drawable
{
public:
	//exception safety/shader variable names
	Shape(GLuint program, vector<float> positions, vector<float> normals, vector<float> texCoords, vector<unsigned int> indices, tinyobj::material_t material);
	~Shape();
	
	void setProjection(glm::mat4 projection);
	void setView(glm::mat4 view);
	
	void setPosition(glm::vec3 position);
	void setRotation(glm::vec3 rotation);
	void setScale(glm::vec3 scale);
	
	virtual void draw() override;
private:
	GLuint program_;
	GLuint vertexArray_;
	
	GLuint positions_;
	GLuint normals_;
	GLuint texCoords_;
	GLuint indices_;
	
	unsigned int indicesCount_;
	
	tinyobj::material_t material_;
	
	GLuint diffuseTex_;
	
	glm::vec3 position_;
	glm::vec3 rotation_;
	glm::vec3 scale_;
};

#endif