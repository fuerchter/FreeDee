#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <memory>
#include <cstdlib>
using namespace std;

#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "tiny_obj_loader.h"

#include "Renderer/Shape.h"

string readFile(string name);
GLuint prepareShader(string code, GLenum type);
GLuint prepareProgram(vector<GLuint> shaders);

int main()
{
	glm::vec2 screenSize(800, 600);

	if(!glfwInit())
	{
		return -1;
	}
	
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);

	GLFWwindow* window=glfwCreateWindow(screenSize.x, screenSize.y, "Test", NULL, NULL);
	if(!window)
	{
		glfwTerminate();
		return -1;
	}
	
	glfwMakeContextCurrent(window);	
	
	glewExperimental=GL_TRUE;
	if(glewInit()!=GLEW_OK)
	{
		glfwTerminate();
		return -1;
	}
	
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	//glEnable(GL_BLEND);
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
	vector<GLuint> shaders;
	string vertex=readFile("vertex.vert");
	shaders.push_back(prepareShader(vertex, GL_VERTEX_SHADER));
	string fragment=readFile("fragment.frag");
	shaders.push_back(prepareShader(fragment, GL_FRAGMENT_SHADER));
	
	GLuint program=prepareProgram(shaders);
	
	string inputfile = "cube.obj";
	vector<tinyobj::shape_t> shapes;

	string err = tinyobj::LoadObj(shapes, inputfile.c_str(), "");

	if (!err.empty()) {
		std::cerr << err << std::endl;
		exit(1);
	}
	
	auto shape=make_shared<Shape>(program, shapes[0].mesh.positions, shapes[0].mesh.normals, shapes[0].mesh.texcoords, shapes[0].mesh.indices, shapes[0].material);
	
	shape->setProjection(glm::perspective(50.0f, screenSize.x/screenSize.y, 0.1f, 1000.0f));
	shape->setView(glm::lookAt(glm::vec3(0, 0, 10), glm::vec3(0,0,0), glm::vec3(0,1,0)));
	
	glm::vec3 rotation;
	
	double time=0;
	double deltaTime=0;
	double fpsTimer=0;
	int fps=0;
	
	while(!glfwWindowShouldClose(window))
	{
		deltaTime=glfwGetTime()-time;
		time=glfwGetTime();
		
		fpsTimer+=deltaTime;
		fps++;
		if(fpsTimer>=1.0)
		{
			cout << fps << endl;
			fps=0;
			fpsTimer=0;
		}
		
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		if(glfwGetKey(window, GLFW_KEY_UP)==GLFW_PRESS)
		{
			rotation.x-=20*deltaTime;
		}
		if(glfwGetKey(window, GLFW_KEY_DOWN)==GLFW_PRESS)
		{
			rotation.x+=20*deltaTime;
		}
		if(glfwGetKey(window, GLFW_KEY_LEFT)==GLFW_PRESS)
		{
			rotation.y-=20*deltaTime;
		}
		if(glfwGetKey(window, GLFW_KEY_RIGHT)==GLFW_PRESS)
		{
			rotation.y+=20*deltaTime;
		}
		shape->setRotation(rotation);
		shape->draw();
		
		if(glfwGetKey(window, GLFW_KEY_ESCAPE)==GLFW_PRESS)
		{
			glfwSetWindowShouldClose(window, GL_TRUE);
		}
		
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	
	shape.reset();
	for(auto shader : shaders)
	{
		glDeleteShader(shader);
	}
	glDeleteProgram(program);
	
	glfwDestroyWindow(window);
	glfwTerminate();
}

string readFile(string name)
{
	string res="";
	ifstream file(name.c_str());
	
	if(file.is_open())
	{
		while(file.good())
		{
			string temp;
			getline(file, temp);
			res+=temp+'\n';
		}
	}
	return res;
}

GLuint prepareShader(string code, GLenum type)
{
	GLuint res=glCreateShader(type);
	
	if(res==0)
	{
		return 0;
	}
	
	const GLchar *newCode[1];
	newCode[0]=code.c_str();
	
	glShaderSource(res, 1, newCode, NULL); //length null because it is a null terminated string
	glCompileShader(res);
	
	GLint compileStatus;
	glGetShaderiv(res, GL_COMPILE_STATUS, &compileStatus);
	if(!compileStatus)
	{
		GLint infoLogLength;
        glGetShaderiv(res, GL_INFO_LOG_LENGTH, &infoLogLength);
        
        GLchar *strInfoLog = new GLchar[infoLogLength + 1];
        glGetShaderInfoLog(res, infoLogLength, NULL, strInfoLog);
		cout << strInfoLog << endl;
		return 0;
	}
	
	return res;
}

GLuint prepareProgram(vector<GLuint> shaders)
{
	GLuint res=glCreateProgram();
	if(res==0)
	{
		return 0;
	}
	
	for(auto shader : shaders)
	{
		glAttachShader(res, shader);
	}
	
	glLinkProgram(res);
	GLint linkStatus;
	glGetProgramiv(res, GL_LINK_STATUS, &linkStatus);
	if(!linkStatus)
	{
		return 0;
	}
	
	glValidateProgram(res);
	GLint valStatus;
	glGetProgramiv(res, GL_VALIDATE_STATUS, &valStatus);
	if(!valStatus)
	{
		return 0;
	}
	
	for(auto shader : shaders)
	{
		glDetachShader(res, shader);
	}
	
	return res;
}