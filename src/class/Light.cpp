#include "../header/Light.h"

Light::Light(vector<Vertex>& vertices, vector<GLuint>& indices, unsigned int type) {
    Light::vertices = vertices;
    Light::indices = indices;
    Light::type = type;

    vao.Bind();
    // Generates Vertex Buffer Object and links it to vertices
    VBO vbo(vertices);
    // Generates Element Buffer Object and links it to indices
    EBO ebo(indices);
    // Links VBO attributes such as coordinates and colors to VAO
    vao.LinkAttrib(vbo, 0, 3, GL_FLOAT, sizeof(Vertex), (void*)0);
    vao.LinkAttrib(vbo, 1, 3, GL_FLOAT, sizeof(Vertex), (void*)(3 * sizeof(float)));
    vao.LinkAttrib(vbo, 2, 3, GL_FLOAT, sizeof(Vertex), (void*)(6 * sizeof(float)));
    vao.LinkAttrib(vbo, 3, 2, GL_FLOAT, sizeof(Vertex), (void*)(9 * sizeof(float)));
    // Unbind all to prevent accidentally modifying them
    vao.Unbind();
    vbo.Unbind();
    ebo.Unbind();
}

void Light::Draw(Shader &shader, Camera &camera) {
    shader.Activate();
    vao.Bind();
    glUniform3f(glGetUniformLocation(shader.ID, "camPos"), camera.Position.x, camera.Position.y, camera.Position.z);
    camera.Matrix(shader, "camMatrix");

    // Draw the actual mesh
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
}