#if defined(_WIN32) || defined(_WIN64)
#include <windows.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <iostream>
#include <vector>
#include <string>

//#define GLEW_STATIC
//#define GLFW_DLL
//#define GLFW_INCLUDE_GLU
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <cstdio>

void controls(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if(action == GLFW_PRESS)
		if(key == GLFW_KEY_ESCAPE)
			glfwSetWindowShouldClose(window, GL_TRUE);
}

GLFWwindow* initWindow(const int resX, const int resY)
{
	glewExperimental = true;
	if(!glfwInit())
	{
		fprintf(stderr, "Failed to initialize GLFW\n");
		return NULL;
	}
	glfwWindowHint(GLFW_SAMPLES, 4); // 4x antialiasing

	// Open a window and create its OpenGL context
	GLFWwindow* window = glfwCreateWindow(resX, resY, "TEST", glfwGetPrimaryMonitor(), NULL);

	if(window == NULL)
	{
		fprintf(stderr, "Failed to open GLFW window.\n");
		glfwTerminate();
		return NULL;
	}

	glfwMakeContextCurrent(window);
	glfwSetKeyCallback(window, controls);

	// Get info of GPU and supported OpenGL version
	printf("Renderer: %s\n", glGetString(GL_RENDERER));
	printf("OpenGL version supported %s\n", glGetString(GL_VERSION));

	glEnable(GL_DEPTH_TEST); // Depth Testing
	glDepthFunc(GL_LEQUAL);
	glDisable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	return window;
}

void display( GLFWwindow* window, char *file )
{
	std::vector<float>			verticeVector;
	std::ifstream infile(file);
	std::string a, b, c;
	float		af, bf, cf;

	while (infile >> a >> b >> c) {
		af = std::stof(a);
		bf = std::stof(b); 
		cf = std::stof(c);
		verticeVector.push_back(af);
		verticeVector.push_back(bf);
		verticeVector.push_back(cf);
	}
	

//	GLfloat *points = &verticeVector[0];
	float points[] = {
		0.0f,  0.5f,  0.0f,
		0.5f, -0.5f,  0.0f,
		-0.5f, -0.5f,  0.0f
	};
	std::cout << "points created\n";

	GLuint vbo = 0;
	std::cout << "vbo init\n"; 
	glGenBuffers(1, &vbo);
	std::cout << "buffer gen\n"; 
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	std::cout << "buffer bind\n"; 
	//glBufferData(GL_ARRAY_BUFFER, verticeVector.size() * sizeof(float), points, GL_STATIC_DRAW);
	glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(float), points, GL_STATIC_DRAW);
	std::cout << "buffer data\n"; 

	std::cout
		<< "HERE: size = "
		<< verticeVector.size()
		<< std::endl
		;

	GLuint vao = 0;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	// shader

	const char* vertex_shader =
		"#version 400\n"
		"in vec3 vp;"
		"void main() {"
		"  gl_Position = vec4(vp, 1.0);"
		"}";

	const char* fragment_shader =
		"#version 400\n"
		"out vec4 frag_colour;"
		"void main() {"
		"  frag_colour = vec4(0.5, 0.0, 0.5, 1.0);"
		"}";

	GLuint vs = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vs, 1, &vertex_shader, NULL);
	glCompileShader(vs);
	GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fs, 1, &fragment_shader, NULL);
	glCompileShader(fs);

	GLuint shader_programme = glCreateProgram();
	glAttachShader(shader_programme, fs);
	glAttachShader(shader_programme, vs);
	glLinkProgram(shader_programme);

	while(!glfwWindowShouldClose(window))
	{
		// Scale to window size
		GLint windowWidth, windowHeight;
		glfwGetWindowSize(window, &windowWidth, &windowHeight);
		glViewport(0, 0, windowWidth, windowHeight);

		// Draw stuff
		glClearColor(0.0, 0.8, 0.3, 1.0);

//		glMatrixMode(GL_PROJECTION_MATRIX);
//		glLoadIdentity();
//		gluPerspective( 60, (double)windowWidth / (double)windowHeight, 0.1, 100 );
//
//		glMatrixMode(GL_MODELVIEW_MATRIX);
//		glTranslatef(0,0,-5);

		// wipe the drawing surface clear
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glUseProgram(shader_programme);
		glBindVertexArray(vao);
		// draw points 0-3 from the currently bound VAO with current in-use shader
		glDrawArrays(GL_TRIANGLES, 0, 3);
		// put the stuff we've been drawing onto the display
		glfwSwapBuffers(window);
		// update other events like input handling 
		glfwPollEvents();
	}
}

int main(int argc, char** argv)
{
	GLFWwindow* window = initWindow(1024, 620);
	glewInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	if( NULL != window )
	{
		display( window, argv[1] );
	}
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}
