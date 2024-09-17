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

using namespace std;



// Vertices coordinates
Vertex vertices[] =
{   //               COORDINATES           /            COLORS          /           NORMALS         /       TEXTURE COORDINATES    //
    Vertex{glm::vec3(-10.0f, 0.0f,  10.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 0.0f)},
    Vertex{glm::vec3(-10.0f, 0.0f, -10.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 1.0f)},
    Vertex{glm::vec3( 10.0f, 0.0f, -10.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(1.0f, 1.0f)},
    Vertex{glm::vec3( 10.0f, 0.0f,  10.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(1.0f, 0.0f)}
};

// Indices for vertices order
GLuint indices[] =
{
    0, 1, 2,
    0, 2, 3
};

// Cria um cubo
Vertex lightVertices[] =
{ //     COORDINATES     //
    Vertex{glm::vec3(-0.1f, -0.1f,  0.1f)},
    Vertex{glm::vec3(-0.1f, -0.1f, -0.1f)},
    Vertex{glm::vec3(0.1f, -0.1f, -0.1f)},
    Vertex{glm::vec3(0.1f, -0.1f,  0.1f)},

    Vertex{glm::vec3(-0.1f,  0.1f,  0.1f)},
    Vertex{glm::vec3(-0.1f,  0.1f, -0.1f)},
    Vertex{glm::vec3(0.1f,  0.1f, -0.1f)},
    Vertex{glm::vec3(0.1f,  0.1f,  0.1f)}
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

// Vertex cubeVertices[] =
// {
//     Vertex{glm::vec3(-1.1f, -1.1f,  1.1f)},
//     Vertex{glm::vec3(-1.1f, -1.1f, -1.1f)},
//     Vertex{glm::vec3(1.1f, -1.1f, -1.1f)},
//     Vertex{glm::vec3(1.1f, -1.1f,  1.1f)},

//     Vertex{glm::vec3(-1.1f,  1.1f,  1.1f)},
//     Vertex{glm::vec3(-1.1f,  1.1f, -1.1f)},
//     Vertex{glm::vec3(1.1f,  1.1f, -1.1f)},
//     Vertex{glm::vec3(1.1f,  1.1f,  1.1f)}
// };

Vertex cubeVertices[] =
{
    //               COORDINATES               /            COLORS          /           NORMALS         /       TEXTURE COORDINATES    //
    Vertex{glm::vec3(-1.1f, -1.1f,  1.1f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 1.0f)}, // ok
    Vertex{glm::vec3(-1.1f, -1.1f, -1.1f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, -1.0f), glm::vec2(0.0f, 0.0f)},// ok
    Vertex{glm::vec3(1.1f, -1.1f, -1.1f),  glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(1.0f, 1.0f, -1.0f), glm::vec2(1.0f, 0.0f)},
    Vertex{glm::vec3(1.1f, -1.1f,  1.1f),  glm::vec3(1.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(1.0f, 1.0f)},

    Vertex{glm::vec3(-1.1f,  1.1f,  1.1f), glm::vec3(1.0f, 0.0f, 1.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0.0f, 1.0f)}, // ok
    Vertex{glm::vec3(-1.1f,  1.1f, -1.1f), glm::vec3(0.0f, 1.0f, 1.0f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec2(0.0f, 0.0f)},// ok
    Vertex{glm::vec3(1.1f,  1.1f, -1.1f),  glm::vec3(1.0f, 0.5f, 0.5f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec2(1.0f, 0.0f)},
    Vertex{glm::vec3(1.1f,  1.1f,  1.1f),  glm::vec3(0.5f, 1.0f, 0.5f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(1.0f, 1.0f)}
};


int main()
{
    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(width, height, "OpenGL Teste", NULL, NULL);
    // Error check if the window fails to create
    if (window == NULL)
    {
        cout << "Failed to create GLFW window" << endl;
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

    Texture textures[] {
        Texture(("../resources/textures/metal.jpg"), "diffuse", 0),
        Texture(("../resources/textures/metal.jpg"), "specular", 1)
    };

    Shader defaultShader("../resources/shaders/default.vert", "../resources/shaders/default.frag");

    vector <Vertex> verts(vertices, vertices + sizeof(vertices) / sizeof(Vertex));
    vector <GLuint> ind(indices, indices + sizeof(indices) / sizeof(GLuint));
    vector <Texture> tex(textures, textures + sizeof(textures) / sizeof(Texture));
    
    Mesh floor(verts, ind, tex); // Mesh plana criada

    Shader lightShader("../resources/shaders/light.vert", "../resources/shaders/light.frag");
    vector <Vertex> lightVerts(lightVertices, lightVertices + sizeof(lightVertices) / sizeof(Vertex));
    vector <GLuint> lightInd(lightIndices, lightIndices + sizeof(lightIndices) / sizeof(GLuint));
    
    Light light(lightVerts, lightInd, 0); // Criando a "mesh" luz, mandadno tex como placeholder
    // Mesh  lightMesh(lightVerts, lightInd, tex);

    vector <Vertex> cubeVerts (cubeVertices, cubeVertices + sizeof(cubeVertices) / sizeof(Vertex));
    Mesh cube(cubeVerts, lightInd, tex);

    glm::vec4 lightColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
    glm::vec3 lightPosition = glm::vec3(0.0f, 0.9f, 0.0f);
    glm::mat4 lightModel = glm::mat4(1.0f);
    unsigned int type = light.type;
    lightModel = translate(lightModel, lightPosition);

    glm::vec3 floorPosition = glm::vec3(0.0f, -0.15f, 0.0f);
    glm::mat4 floorModel = glm::mat4(1.0f);
    floorModel = translate(floorModel, floorPosition);

    glm::mat4 cubeModel = floorModel;

    lightShader.Activate();
    glUniformMatrix4fv(glGetUniformLocation(lightShader.ID, "model"), 1, GL_FALSE, value_ptr(lightModel));
    glUniform4f(glGetUniformLocation(lightShader.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);

    defaultShader.Activate();
    glUniformMatrix4fv(glGetUniformLocation(defaultShader.ID, "model"), 1, GL_FALSE, value_ptr(floorModel));
    glUniform4f(glGetUniformLocation(defaultShader.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
    glUniform3f(glGetUniformLocation(defaultShader.ID, "lightPos"), lightPosition.x, lightPosition.y, lightPosition.z);
    glUniform1ui(glGetUniformLocation(defaultShader.ID, "type"), type);

    Model model("../resources/models/bunny2/scene.gltf");

    glEnable(GL_DEPTH_TEST);

    Camera camera(width, height, glm::vec3(0.0f, 0.0f, 2.0f));

    // Main while loop
    while (!glfwWindowShouldClose(window))
    {
        // Specify the color of the background
        glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
        // Clean the back buffer and assign the new color to it
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        // Tell OpenGL which Shader Program we want to use

        camera.Inputs(window);
        camera.updateMatrix(45.0f, 0.1f, 100.0f);

        // light.Draw(lightShader, camera);
        model.Draw(defaultShader, camera);
        // floor.Draw(defaultShader, camera, floorModel);
        cube.Draw(defaultShader, camera, cubeModel);
        // Swap the back buffer with the front buffer
        glfwSwapBuffers(window);
        // Take care of all GLFW events
        glfwPollEvents();
    }
    // Delete all the objects we've created
    defaultShader.Delete();
    lightShader.Delete();
    // Delete window before ending the program
    glfwDestroyWindow(window);
    // Terminate GLFW before ending the program
    glfwTerminate();
    return 0;
}