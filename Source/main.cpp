#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

int WindowSizeX = 640;
int WindowSizeY = 480;

void glfwWindowSizeCallBack(GLFWwindow* Window, int Widgh, int Height)
{
	WindowSizeX = Widgh; WindowSizeY = Height;
	glViewport(0,0, WindowSizeX, WindowSizeY);
}

void glfwKeyCallback(GLFWwindow* Window, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(Window, GL_TRUE);
	}
}

int main(void)
{
	/* Initialize the library */
	if (!glfwInit())
	{
		std::cout << "glfwInit failed!" << std::endl;
		return -1;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	/* Create a windowed mode window and its OpenGL context */
	GLFWwindow* window = glfwCreateWindow(WindowSizeX, WindowSizeY, "Battle city", NULL, NULL);
	if (!window)
	{
		std::cout << "glfwCreateWindow failed!" << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwSetWindowSizeCallback(window, glfwWindowSizeCallBack);
	glfwSetKeyCallback(window, glfwKeyCallback);

	/* Make the window's context current */
	glfwMakeContextCurrent(window);
	
	if (!gladLoadGL())
	{
		std::cout<<"Cant load glad!"<<std::endl;
		return -1;
	}
	
	std::cout << "Renderer" << glGetString(GL_RENDERER) << std::endl;
	std::cout<<"OpenGL version"<<glGetString(GL_VERSION)<<std::endl;
	
	glClearColor(1,1,0,1);
	
	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT);

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}