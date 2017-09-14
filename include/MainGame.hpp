#pragma once

#include <GL/glew.h>
#include "glm/glm.hpp"
#include "glfw3.h"
#include <iostream>

class MainGame {
	public:
		MainGame();
		~MainGame();

		void	run();

		void	initSystems();
	private:
		GLFWwindow	*window;

};
