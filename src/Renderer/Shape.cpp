#include "Shape.h"

Shape::Shape(GLuint program, vector<float> positions, vector<float> normals, vector<float> texCoords, vector<unsigned int> indices, tinyobj::material_t material):
program_(program), indicesCount_(indices.size()), material_(material), scale_(1.0f, 1.0f, 1.0f)
{
	glGenVertexArrays(1, &vertexArray_);
	glBindVertexArray(vertexArray_);
	
	//Upload vertex data to the attribute
	glGenBuffers(1, &positions_);
	glBindBuffer(GL_ARRAY_BUFFER, positions_);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float)*positions.size(), &positions[0], GL_STATIC_DRAW);
	
	GLint positionLocation=glGetAttribLocation(program_, "position");
	glEnableVertexAttribArray(positionLocation);
	glVertexAttribPointer(positionLocation, 3, GL_FLOAT, GL_FALSE, 0, NULL); //3=numbers per vertex
	
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	
	//Upload normal data to the attribute
	glGenBuffers(1, &normals_);
	glBindBuffer(GL_ARRAY_BUFFER, normals_);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float)*normals.size(), &normals[0], GL_STATIC_DRAW);
	
	GLint normalLocation=glGetAttribLocation(program_, "normal");
	glEnableVertexAttribArray(normalLocation);
	glVertexAttribPointer(normalLocation, 3, GL_FLOAT, GL_FALSE, 0, NULL); //3=numbers per normal
	
	//Upload texture coordinates
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	
	glGenBuffers(1, &texCoords_);
	glBindBuffer(GL_ARRAY_BUFFER, texCoords_);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float)*texCoords.size(), &texCoords[0], GL_STATIC_DRAW);
	
	GLint textureCoordLocation=glGetAttribLocation(program, "texCoord");
	glEnableVertexAttribArray(textureCoordLocation);
	glVertexAttribPointer(textureCoordLocation, 2, GL_FLOAT, GL_FALSE, 0, NULL); //2=numbers per coordinate
	
	if(material.diffuse_texname!="")
	{		
		StbImage texture(material.diffuse_texname);
		texture.flipY();
		
		glGenTextures(1, &diffuseTex_);
		glBindTexture(GL_TEXTURE_2D, diffuseTex_);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexImage2D(GL_TEXTURE_2D, 0, 
					 GL_RGBA,
					 (GLsizei)texture.getSize().x, 
					 (GLsizei)texture.getSize().y,
					 0, 
					 GL_RGBA, 
					 GL_UNSIGNED_BYTE, 
					 &texture.getPixels()[0]);
		
		glBindTexture(GL_TEXTURE_2D, 0);
		
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
	
	//Save indices in buffer
	glGenBuffers(1, &indices_);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indices_);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int)*indices.size(), &indices[0], GL_STATIC_DRAW);
	
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	
	glBindVertexArray(0);
}

Shape::~Shape()
{
	glDeleteBuffers(1, &positions_);
	glDeleteBuffers(1, &normals_);
	glDeleteBuffers(1, &texCoords_);
	glDeleteBuffers(1, &indices_);
	
	glDeleteTextures(1, &diffuseTex_);
}

void Shape::setProjection(glm::mat4 projection)
{
	glUseProgram(program_);
	GLint projectionLocation=glGetUniformLocation(program_, "projection");
	glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, &projection[0][0]);
}

void Shape::setView(glm::mat4 view)
{
	glUseProgram(program_);
	GLint viewLocation=glGetUniformLocation(program_, "view");
	glUniformMatrix4fv(viewLocation, 1, GL_FALSE, &view[0][0]);
}

void Shape::setPosition(glm::vec3 position)
{
	position_=position;
}

void Shape::setRotation(glm::vec3 rotation)
{
	rotation_=rotation;
}

void Shape::setScale(glm::vec3 scale)
{
	scale_=scale;
}

void Shape::draw()
{
	glUseProgram(program_);
		
    glBindVertexArray(vertexArray_);
	
	//Create transformations
	glm::mat4 model;
	model=glm::translate(model, position_);
	model=glm::scale(model, scale_);
	model=glm::rotate(model, rotation_.x, glm::vec3(1, 0, 0));
	model=glm::rotate(model, rotation_.y, glm::vec3(0, 1, 0)); 	
	model=glm::rotate(model, rotation_.z, glm::vec3(0, 0, 1)); 
	
	GLint modelLocation=glGetUniformLocation(program_, "model");
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, &model[0][0]);
	
	//Upload diffuse color
	GLint diffuseLocation=glGetUniformLocation(program_, "diffuse");
	glUniform3fv(diffuseLocation, 1, material_.diffuse);
	
	//Upload diffuse texture
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, diffuseTex_);
	GLint diffuseTexLocation=glGetUniformLocation(program_, "diffuseTex");
	glUniform1i(diffuseTexLocation, 0);
	
	//TEST LIGHT STUFF
	GLfloat lightPosition[]={0, 0, 10};
	GLint lightPositionLocation=glGetUniformLocation(program_, "lightPosition");
	glUniform3fv(lightPositionLocation, 1, lightPosition);
	
	GLfloat lightColor[]={1, 1, 1};
	GLint lightColorLocation=glGetUniformLocation(program_, "lightColor");
	glUniform3fv(lightColorLocation, 1, lightColor);
	
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indices_);
    glDrawElements(GL_TRIANGLES, indicesCount_, GL_UNSIGNED_INT, 0);
}