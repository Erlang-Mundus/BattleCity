#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

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

const char* vertex_shader =
"#version 460\n"
"layout(location = 0) in vec3 vertex_position;"
"layout(location = 1) in vec3 vertex_color;"
"out vec3 color;"
"void main(){"
"	color = vertex_color;"
"	gl_Position = vec4(vertex_position, 1.0);"
"}";

const char* fragment_shader =
"#version 460\n"
"in vec3 color;"
"out vec4 frag_color;"
"void main(){"
"	frag_color = vec4 (color, 1.0);"
"}";

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
	
	GLuint vs = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vs, 1, &vertex_shader,nullptr);
	glCompileShader(vs);

	GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fs, 1, &fragment_shader, nullptr);
	glCompileShader(fs);

	GLuint ShaderProgram = glCreateProgram();
	glAttachShader(ShaderProgram, vs);
	glAttachShader(ShaderProgram, fs);
	glLinkProgram(ShaderProgram);

	glDeleteShader(vs);
	glDeleteShader(fs);

	// Generate buffers
	GLuint PointsVBO = 0;
	glGenBuffers(1, &PointsVBO);
	glBindBuffer(GL_ARRAY_BUFFER, PointsVBO);
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
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, ColorsVBO);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(ShaderProgram);
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}