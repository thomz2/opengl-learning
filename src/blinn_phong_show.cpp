#include "./header/Mesh.h"
#include "./header/Light.h"
#include "./header/Model.h"
#include <vector>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <math.h>
#include <glm/glm.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <stb/stb_image.h>

#include "header/shaderClass.h"
#include "header/VBO.h"
#include "header/VAO.h"
#include "header/EBO.h"
#include "header/Camera.h"
#include "header/Texture.h"

const unsigned int width = 800;
const unsigned int height = 800;

// Vertices coordinates
GLfloat vertices[] =
{ //     COORDINATES        /        COLORS         /    TexCoord       /       NORMALS      //
	-10.0f, 0.0f,  10.0f,		0.0f, 0.0f, 0.0f,		0.0f,   0.0f,		0.0f, 1.0f, 0.0f,
	-10.0f, 0.0f, -10.0f,		0.0f, 0.0f, 0.0f,		0.0f,  10.0f,		0.0f, 1.0f, 0.0f,
	 10.0f, 0.0f, -10.0f,		0.0f, 0.0f, 0.0f,		10.0f, 10.0f,		0.0f, 1.0f, 0.0f,
	 10.0f, 0.0f,  10.0f,		0.0f, 0.0f, 0.0f,		10.0f,  0.0f,		0.0f, 1.0f, 0.0f
};

// Indices for vertices order
GLuint indices[] =
{
	0, 1, 2,
	0, 2, 3
};

GLfloat lightVertices[] =
{ //     COORDINATES     //
	-0.05f, -0.05f,  0.05f,
	-0.05f, -0.05f, -0.05f,
	 0.05f, -0.05f, -0.05f,
	 0.05f, -0.05f,  0.05f,

	-0.05f,  0.05f,  0.05f,
	-0.05f,  0.05f, -0.05f,
	 0.05f,  0.05f, -0.05f,
	 0.05f,  0.05f,  0.05f
};

GLuint lightIndices[] =
{
	0, 1, 2,
	0, 2, 3,
	0, 4, 7,
	0, 7, 3,
	3, 7, 6,
	3, 6, 2,
	2, 6, 5,
	2, 5, 1,
	1, 5, 4,
	1, 4, 0,
	4, 5, 6,
	4, 6, 7
};

// Vertices para a parede de tijolo
std::vector<Vertex> rectangleVerticesVector =
{ //    COORDINATES     /                 normals                     / colors                     / texture
	Vertex{glm::vec3(-1.0f, -2.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec2(0.0f, 1.0f)},
	Vertex{glm::vec3(-1.0f, 0.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec2(1.0f, 1.0f)},
	Vertex{glm::vec3(-1.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec2(1.0f, 0.0f)},
	Vertex{glm::vec3(-1.0f, -2.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec2(0.0f, 0.0f)}
};

// Indices para a parede de tijolo
std::vector<GLuint> rectangleIndices =
{
	0, 1, 2,
	0, 2, 3
};

int main()
{
	// Initialize GLFW
	glfwInit();

	// Tell GLFW what version of OpenGL we are using 
	// In this case we are using OpenGL 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// Tell GLFW we are using the CORE profile
	// So that means we only have the modern functions
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(width, height, "Projeto Thomaz e Gabriel", NULL, NULL);
	// Error check if the window fails to create
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	// Introduce the window into the current context
	glfwMakeContextCurrent(window);

	//Load GLAD so it configures OpenGL
	gladLoadGL();
	// Specify the viewport of OpenGL in the Window
	// In this case the viewport goes from x = 0, y = 0, to x = 800, y = 800
	glViewport(0, 0, width, height);

	// Generates Shader object using shaders default.vert and default.frag
	Shader shaderProgram("../resources/shaders/default.vert", "../resources/shaders/default.frag");
	// Generates Vertex Array Object and binds it
	VAO VAO1;
	VAO1.Bind();
	// Generates Vertex Buffer Object and links it to vertices
	VBO VBO1(vertices, sizeof(vertices));
	// Generates Element Buffer Object and links it to indices
	EBO EBO1(indices, sizeof(indices));
	// Links VBO attributes such as coordinates and colors to VAO
	VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 11 * sizeof(float), (void*)0);
	VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 11 * sizeof(float), (void*)(3 * sizeof(float)));
	VAO1.LinkAttrib(VBO1, 2, 2, GL_FLOAT, 11 * sizeof(float), (void*)(6 * sizeof(float)));
	VAO1.LinkAttrib(VBO1, 3, 3, GL_FLOAT, 11 * sizeof(float), (void*)(8 * sizeof(float)));
	// Unbind all to prevent accidentally modifying them
	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();


	// Shader for light cube
	Shader lightShader("../resources/shaders/light.vert", "../resources/shaders/light.frag");
	// Generates Vertex Array Object and binds it
	VAO lightVAO;
	lightVAO.Bind();
	// Generates Vertex Buffer Object and links it to vertices
	VBO lightVBO(lightVertices, sizeof(lightVertices));
	// Generates Element Buffer Object and links it to indices
	EBO lightEBO(lightIndices, sizeof(lightIndices));
	// Links VBO attributes such as coordinates and colors to VAO
	lightVAO.LinkAttrib(lightVBO, 0, 3, GL_FLOAT, 3 * sizeof(float), (void*)0);
	// Unbind all to prevent accidentally modifying them
	lightVAO.Unbind();
	lightVBO.Unbind();
	lightEBO.Unbind();

	glm::vec4 lightColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	glm::vec3 lightPos = glm::vec3(0.0f, 0.9f, 0.0f);
	glm::mat4 lightModel = glm::mat4(1.0f);
	lightModel = glm::translate(lightModel, lightPos);

	glm::vec3 objectPos = glm::vec3(0.0f, 0.06f, 0.0f);
	glm::mat4 objectModel = glm::mat4(1.0f);
	objectModel = glm::translate(objectModel, objectPos);


	lightShader.Activate();
	glUniformMatrix4fv(glGetUniformLocation(lightShader.ID, "model"), 1, GL_FALSE, glm::value_ptr(lightModel));
	glUniform4f(glGetUniformLocation(lightShader.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
	shaderProgram.Activate();
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram.ID, "model"), 1, GL_FALSE, glm::value_ptr(objectModel));
	glUniform4f(glGetUniformLocation(shaderProgram.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
	glUniform3f(glGetUniformLocation(shaderProgram.ID, "lightPos"), lightPos.x, lightPos.y, lightPos.z);

	Shader brickShader(
		"../resources/shaders/object.vert",
		"../resources/shaders/brick.frag" 
	);
	brickShader.Activate();
	glUniform4f(glGetUniformLocation(brickShader.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
	glUniform3f(glGetUniformLocation(brickShader.ID, "lightPos"), lightPos.x, lightPos.y, lightPos.z);

	// Textures
	Texture planksTex("../resources/textures/madeira.png", 0, GL_RGBA, GL_UNSIGNED_BYTE);
	planksTex.texUnit(shaderProgram, "tex0", 0);
	Texture planksSpec("../resources/textures/madeiraSpec.png", 1, GL_RED, GL_UNSIGNED_BYTE);
	planksSpec.texUnit(shaderProgram, "tex1", 1);

    Shader modelShader("../resources/shaders/object.vert", "../resources/shaders/object.frag");
    Model model("../resources/models/bunny2/scene.gltf");
	modelShader.Activate();
    glUniformMatrix4fv(glGetUniformLocation(modelShader.ID, "model"), 1, GL_FALSE, value_ptr(objectModel));
    glUniform4f(glGetUniformLocation(modelShader.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
    glUniform3f(glGetUniformLocation(modelShader.ID, "lightPos"), lightPos.x, lightPos.y, lightPos.z);
    glUniform1ui(glGetUniformLocation(modelShader.ID, "type"), 1);

	std::vector<Texture> textures =
	{
		Texture("../resources/textures/diffuse.png", "diffuse", 0)
	};

	// Plane with the texture
	Mesh plane(rectangleVerticesVector, rectangleIndices, textures);

	// Normal map for the plane
	Texture normalMap("../resources/textures/normal.png", "normal", 1);
	// Texture displacementMap("../resources/textures/displacement.png", "displacement", 2);

	// Enables the Depth Buffer
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	

	// Creates camera object
	Camera camera(width, height, glm::vec3(-1.90f, 0.5f, -0.01f));

	// Main while loop
	while (!glfwWindowShouldClose(window))
	{
		// Specify the color of the background
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		// Clean the back buffer and depth buffer
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Handles camera inputs
		camera.Inputs(window);
		// Updates and exports the camera matrix to the Vertex Shader
		camera.updateMatrix(45.0f, 0.1f, 100.0f);
		// cout << camera.Position.x << " " << camera.Position.y << " " << camera.Position.z << endl;

		// Tells OpenGL which Shader Program we want to use
		shaderProgram.Activate();		
		// Exports the camera Position to the Fragment Shader for specular lighting
		glUniform3f(glGetUniformLocation(shaderProgram.ID, "camPos"), camera.Position.x, camera.Position.y, camera.Position.z);
		// Export the camMatrix to the Vertex Shader of the pyramid
		camera.Matrix(shaderProgram, "camMatrix");
		// Binds textures so that they appear in the rendering
		planksTex.Bind();
		planksSpec.Bind();
		// Bind the VAO so OpenGL knows to use it
		VAO1.Bind();
		// Draw primitives, number of indices, datatype of indices, index of indices
		glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(int), GL_UNSIGNED_INT, 0);

		model.Draw(modelShader, camera);

		brickShader.Activate();
		normalMap.Bind();
		glUniform1i(glGetUniformLocation(brickShader.ID, "normal0"), 1);
		// displacementMap.Bind();
		// glUniform1i(glGetUniformLocation(brickShader.ID, "displacement0"), 2);
		plane.Draw(brickShader, camera);

		// Tells OpenGL which Shader Program we want to use
		lightShader.Activate();
		// Export the camMatrix to the Vertex Shader of the light cube
		camera.Matrix(lightShader, "camMatrix");
		// Bind the VAO so OpenGL knows to use it
		lightVAO.Bind();
		// Draw primitives, number of indices, datatype of indices, index of indices
		// glDrawElements(GL_TRIANGLES, sizeof(lightIndices) / sizeof(int), GL_UNSIGNED_INT, 0);


		// Swap the back buffer with the front buffer
		glfwSwapBuffers(window);
		// Take care of all GLFW events
		glfwPollEvents();
	}



	// Delete all the objects we've created
	VAO1.Delete();
	VBO1.Delete();
	EBO1.Delete();
	planksTex.Delete();
	planksSpec.Delete();
	shaderProgram.Delete();
	lightVAO.Delete();
	lightVBO.Delete();
	lightEBO.Delete();
	lightShader.Delete();
	// Delete window before ending the program
	glfwDestroyWindow(window);
	// Terminate GLFW before ending the program
	glfwTerminate();
	return 0;
}