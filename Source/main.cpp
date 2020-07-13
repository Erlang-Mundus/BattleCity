#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <string>

#include "Renderer/ShaderProgram.h"
#include "Resource/ResourceManager.h"

GLfloat Points[] = {
	0.0f,0.5f,0.0f,
	0.5f,-0.5f,0.0f,
	-0.5f,-0.5f,0.0f
};

GLfloat Colors[] = {
	1.0f,0.0f,0.0f,
	0.0f,1.0f,0.0f,
	0.0f,0.0f,1.0f,
};

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

int main(int argc, char**argv)
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

	{
		ResourceManager ResourceManager(argv[0]);
		auto DefaultShaderProgram = ResourceManager.LoadShader("DefaultShader", "Content/Shader/VertexShader.txt", "Content/Shader/FragmentShader.txt");

		if (!DefaultShaderProgram)
		{
			std::cout << "Cant load shader program" << std::endl;
			return -1;
		}

		// Generate buffers
		GLuint PointsVBO = 0;
		glGenBuffers(1, &PointsVBO);
		//set active buffer
		glBindBuffer(GL_ARRAY_BUFFER, PointsVBO);
		//load data from ram to gpu mem
		glBufferData(GL_ARRAY_BUFFER, sizeof(Points), Points, GL_STATIC_DRAW);

		GLuint ColorsVBO = 0;
		glGenBuffers(1, &ColorsVBO);
		glBindBuffer(GL_ARRAY_BUFFER, ColorsVBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(Colors), Colors, GL_STATIC_DRAW);

		GLuint VAO = 0;
		glGenVertexArrays(1, &VAO);
		glBindVertexArray(VAO);

		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, PointsVBO);
		//link vertex data with shader
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, ColorsVBO);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

		/* Loop until the user closes the window */
		while (!glfwWindowShouldClose(window))
		{
			/* Render here */
			glClear(GL_COLOR_BUFFER_BIT);

			DefaultShaderProgram->Use();
			glBindVertexArray(VAO);
			// draw current vertex array object
			glDrawArrays(GL_TRIANGLES, 0, 3);

			/* Swap front and back buffers */
			glfwSwapBuffers(window);

			/* Poll for and process events */
			glfwPollEvents();
		}
	}

	glfwTerminate();
	return 0;
}