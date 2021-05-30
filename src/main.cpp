// GLAD goes first
#include "glad/glad.h"
// GLFW goes second
#include "glfw3.h"
#include "Shader.h"
#include "../dependencies/stb_image/stb_image.h"
#include <iostream>

bool VAO_MODE = true;

void framebuffer_size_callback(GLFWwindow*, int width, int height)
{
	glViewport(-1, -1, width, height);
}

void process_input(GLFWwindow* m_window)
{
	if(glfwGetKey(m_window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(m_window, true);
	} else if (glfwGetKey(m_window, GLFW_KEY_1) == GLFW_PRESS)
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	} else if (glfwGetKey(m_window, GLFW_KEY_2) == GLFW_PRESS)
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
	else if (glfwGetKey(m_window, GLFW_KEY_3) == GLFW_PRESS)
	{
		VAO_MODE = false;
	}
	else if (glfwGetKey(m_window, GLFW_KEY_4) == GLFW_PRESS)
	{
		VAO_MODE = true;
	}
}

const char *vertex_shader_source = 
	"#version 330 core\n"
	"layout (location = 0) in vec3 aPos;\n"
	"layout (location = 1) in vec3 aColor;\n"
	"out vec3 color;\n"
    "void main()\n"
    "{\n"
	"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
	"   color = aColor;\n"
	"}\0";
const char *fragment_shader_source =
	"#version 330 core\n"
	"out vec4 FragColor;\n"
	"uniform vec4 ourColor;\n"
	"in vec3 color;\n"
	"void main()\n"
	"{\n"
	"   FragColor = vec4(color, 1.0f);\n"
	"}\0";

int main()
{
	float vertices[] = {
		-0.5f, -0.5f, 0.0f, 0.5f, 0.f, 0.0f,  1.f, 1.f,
		 0.5f, -0.5f, 0.0f, 0.5f, 0.5f, 0.0f, 1.f, 0.f,
		 0.5f, 0.5f, 0.0f,  0.f, 0.5f, 0.0f,  0.f, 0.f,
		-0.5f, 0.5f, 0.0f,  0.5f, 0.5f, 0.0f, 0.f, 1.f
	};
	float vertices_triangle[] = {
		0.f, 0.f, 0.f,
		1.f, 0.f, 0.f,
		.5f, 1.f, 0.f
	};
	float tex_coordinates[] = {
		0.f, 0.f, 0.f,
		1.f, 0.f, 0.f,
		.5f, 1.f, 0.f
	};
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, 
	GLFW_OPENGL_CORE_PROFILE);
	
	GLFWwindow* m_window = glfwCreateWindow(800,600,
	"LearnOpenGL", nullptr, nullptr);
	if(m_window == nullptr)
	{
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(m_window);
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Error loading GLAD.";
		return -1;
	} else
	{
		std::cout << "Glad loaded.\n";
	}
	// CALLBACK FOR RESIZE WINDOW
	framebuffer_size_callback(m_window, 800,600);
	glfwSetFramebufferSizeCallback(m_window, framebuffer_size_callback);
	// CREATE SHADER INSTANCE AND PROGRAM
	Shader my_shader("resources/shaders/basic_shader.vs",
	"resources/shaders/basic_shader.fs");

	// VERTEX BUFFER OBJECT (GPU)
	unsigned int VBO;
	glGenBuffers(1, & VBO);
	// VERTEX ARRAY OBJECT
	unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	// ELEMENT BUFFER OBJECT
	unsigned int indices[] = {
		0,1,2,
		0,2,3
	};
	unsigned int EBO;
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	// POSITION FOR VERTEX SHADER (location 0)
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// COLOR FOR VERTEX SHADER (location 1)
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3*sizeof(float)));
	glEnableVertexAttribArray(1);
	// TEXTURE COORDINATES FOR THE SHADER
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	// VERTEX BUFFER OBJECT (GPU)
	unsigned int VBO_triangle;
	glGenBuffers(1, &VBO_triangle);
	// VERTEX ARRAY OBJECT
	unsigned int VAO_triangle;
	glGenVertexArrays(1, &VAO_triangle);
	glBindVertexArray(VAO_triangle);
	glBindBuffer(GL_ARRAY_BUFFER, VBO_triangle);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_triangle), vertices_triangle, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// Load Texture 1
	stbi_set_flip_vertically_on_load(true);
	int width, heigth, nr_channels;
	unsigned char* texture_data = stbi_load("resources/textures/container.jpg",
		&width, &heigth, &nr_channels, 0);
	unsigned int texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, heigth, 0, GL_RGB, GL_UNSIGNED_BYTE,
		texture_data);
	glGenerateMipmap(GL_TEXTURE_2D);
	stbi_image_free(texture_data);
	// Load Texture 2
	int width2, heigth2, nr_channels2;
	unsigned char* texture_data2 = stbi_load("resources/textures/awesomeface.png",
		&width2, &heigth2, &nr_channels2, 0);
	unsigned int texture2;
	glGenTextures(1, &texture2);
	glBindTexture(GL_TEXTURE_2D, texture2);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width2, heigth2, 0, GL_RGBA, GL_UNSIGNED_BYTE,
		texture_data2);
	glGenerateMipmap(GL_TEXTURE_2D);
	stbi_image_free(texture_data2);

	//Render loop
	while(!glfwWindowShouldClose(m_window))
	{
		process_input(m_window);
		//All the rendering things
		glClearColor(0.2f, 0.1f, 0.5f, 1.f);
		glClear(GL_COLOR_BUFFER_BIT);
		float time_value = glfwGetTime();
		float green = (sin(time_value)/2.f)+ .5f;
		// LINKING VERTEX ATTRIBUTES
		my_shader.use();
		my_shader.setFloat("green", green);
		my_shader.setInt("texture1", 0);
		my_shader.setInt("texture2", 1);
		//Draw
		if(VAO_MODE)
		{
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, texture);
			glActiveTexture(GL_TEXTURE0+1);
			glBindTexture(GL_TEXTURE_2D, texture2);
			glBindVertexArray(VAO);
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
		}else
		{
			glBindVertexArray(VAO_triangle);
			glDrawArrays(GL_TRIANGLES, 1, 3);
		}
			
		glBindVertexArray(0);
		// poll the events and call the callback functions.
		glfwPollEvents();
		// swap the Color buffer
		glfwSwapBuffers(m_window);
	}
	return 0;
}
