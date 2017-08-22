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

#define GLEW_STATIC
//#include <GL/glew.h>
//#include <GL/gl.h>
//#include <GL/glew.h>

#define GLFW_INCLUDE_GLU
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

void draw(char *file)
{
	// read file into string array
	// cast string array into float array
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
	
	GLfloat *vertices = &verticeVector[0];

/*	GLfloat colors[] =
	{
		0, 0, 0,   0, 0, 1,   0, 1, 1,   0, 1, 0,
		1, 0, 0,   1, 0, 1,   1, 1, 1,   1, 1, 0,
		0, 0, 0,   0, 0, 1,   1, 0, 1,   1, 0, 0,
		0, 1, 0,   0, 1, 1,   1, 1, 1,   1, 1, 0,
		0, 0, 0,   0, 1, 0,   1, 1, 0,   1, 0, 0,
		0, 0, 1,   0, 1, 1,   1, 1, 1,   1, 0, 1
	};
*/
	static float alpha = 0;
	//attempt to rotate cube
	glRotatef(alpha, 0, 1, 0);

	/* We have a color array and a vertex array */
	glEnableClientState(GL_VERTEX_ARRAY);
//	glEnableClientState(GL_COLOR_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, vertices);
//	glColorPointer(3, GL_FLOAT, 0, colors);

	/* Send data : 24 vertices */
	glDrawArrays(GL_QUADS, 0, 23);

	/* Cleanup states */
//	glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
	alpha += 1;
}

void display( GLFWwindow* window, char *file )
{
	while(!glfwWindowShouldClose(window))
	{
		// Scale to window size
		GLint windowWidth, windowHeight;
		glfwGetWindowSize(window, &windowWidth, &windowHeight);
		glViewport(0, 0, windowWidth, windowHeight);

		// Draw stuff
		glClearColor(0.0, 0.8, 0.3, 1.0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glMatrixMode(GL_PROJECTION_MATRIX);
		glLoadIdentity();
		gluPerspective( 60, (double)windowWidth / (double)windowHeight, 0.1, 100 );

		glMatrixMode(GL_MODELVIEW_MATRIX);
		glTranslatef(0,0,-5);

		draw(file);

		// Update Screen
		glfwSwapBuffers(window);

		// Check for any input, or window movement
		glfwPollEvents();
	}
}

int main(int argc, char** argv)
{
	GLFWwindow* window = initWindow(1024, 620);
	if( NULL != window )
	{
		display( window, argv[1] );
	}
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}
