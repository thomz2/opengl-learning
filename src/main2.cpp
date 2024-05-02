#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <math.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "header/shaderClass.h"
#include "header/VBO.h"
#include "header/VAO.h"
#include "header/EBO.h"

using namespace std;

const char* vertexShaderSource = R"glsl(
#version 330 core
layout (location = 0) in vec3 aPos;

void main()
{
    gl_Position = vec4(aPos, 1.0);
}
)glsl";

const char* fragmentShaderSource = R"glsl(
#version 330 core
out vec4 FragColor;
void main()
{
    FragColor = vec4(0.8f, 0.3f, 0.02f, 1.0f);
}
)glsl";

int main() {

    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(800, 800, "Apresentação :)", NULL, NULL);
    if (window == NULL)
    {
        cout << "Failed to create GLFW window" << endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    gladLoadGL();
    glViewport(0, 0, 800, 800);

    GLfloat vertices[] =
    {
        // -0.5f, -0.5f * float(sqrt(3)) / 3,    0.5f,  0.8f, 0.3f, 0.02f,
        //  0.5f, -0.5f * float(sqrt(3)) / 3,    0.0f,  0.8f, 0.3f, 0.02f,
        //  0.0f, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f,  1.0f, 0.6f, 0.32f,
        // -0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f,  0.9f, 0.45f, 0.17f,
        //  0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f,  0.9f, 0.45f, 0.17f,
        //  0.0f, -0.5f * float(sqrt(3)) / 3,    0.5f,  0.8f, 0.3f, 0.02f,

        -0.5f,  0.0f,  0.5f,  0.8f, 0.3f, 0.02f,
        -0.5f,  0.0f, -0.5f,  0.8f, 0.3f, 0.02f,
         0.5f,  0.0f, -0.5f,  1.0f, 0.6f, 0.32f,
         0.5f,  0.0f,  0.5f,  0.9f, 0.45f, 0.17f,
         0.0f,  0.8f , 0.0f,  0.8f, 0.3f, 0.02f,
    };

    GLuint indices[] = 
    {
        // 0, 3, 5,
        // 3, 2, 4,
        // 5, 4, 1

        0, 1, 2,
        0, 2, 3,
        0, 1, 4,
        1, 2, 4,
        2, 3, 4,
        3, 0, 4
    };

    Shader shaderProgram("../resources/shaders/default.vert", "../resources/shaders/default.frag");

    VAO VAO1;
    VAO1.Bind();

    VBO VBO1(vertices, sizeof(vertices));
    EBO EBO1(indices, sizeof(indices));

    VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 6 * sizeof(float), (void*)0);
    VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    VAO1.Unbind();
    VBO1.Unbind();
    EBO1.Unbind();

    GLuint uniID = glGetUniformLocation(shaderProgram.ID, "scale");

    float rotation = 0.0f;
    double prevTime = glfwGetTime();

    glEnable(GL_DEPTH_TEST);

    while (!glfwWindowShouldClose(window))
    {
        glClearColor(0.5f, 0.7f, 0.9f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        // glUseProgram(shaderProgram);
        shaderProgram.Activate();

        glm::mat4 model = glm::mat4(1.0f);
        glm::mat4 view = glm::mat4(1.0f);
        glm::mat4 proj = glm::mat4(1.0f);

        double crntTime = glfwGetTime();
        if (crntTime - prevTime >= 1 / 60)
        {
            rotation += 0.05f;
            prevTime = crntTime;
        }

        model = glm::rotate(model, glm::radians(rotation), glm::vec3(0.0f, 1.0f, 0.0f));
        view = glm::translate(view, glm::vec3(0.0f, -0.5f, -2.0f));
        proj = glm::perspective(glm::radians(45.0f), (float)(800/800), 0.1f, 100.0f);

        int modelLoc = glGetUniformLocation(shaderProgram.ID, "model");
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

        int viewLoc = glGetUniformLocation(shaderProgram.ID, "view");
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));

        int projLoc = glGetUniformLocation(shaderProgram.ID, "proj");
        glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(proj));

        glUniform1f(uniID, 0.5f);
        // glBindVertexArray(VAO);
        VAO1.Bind();
        // glDrawArrays(GL_TRIANGLES, 0, 3);
        glDrawElements(GL_TRIANGLES, sizeof(indices)/sizeof(int), GL_UNSIGNED_INT, 0);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    
    VAO1.Delete();
    VBO1.Delete();
    EBO1.Delete();
    shaderProgram.Delete();
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
