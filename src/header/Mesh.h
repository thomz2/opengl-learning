#ifndef MESH_CLASS_H
#define MESH_CLASS_H

#include <string>
#include "../header/Camera.h"
#include "../header/EBO.h"
#include "../header/VAO.h"
#include "../header/Texture.h"
#include "../header/Vertex.h"

#include <vector>

using namespace std;

class Mesh{

public:
    vector <Vertex> vertices;
    vector <GLuint> indices;
    vector <Texture> textures;

    VAO vao;

    Mesh(vector <Vertex>& vertices, vector <GLuint>& indices, vector <Texture>& textures);

    void Draw
    (
        Shader& shader,
        Camera& camera,
        glm::mat4 matrix = glm::mat4(1.0f),
        glm::vec3 translation = glm::vec3(0.0f, 0.0f, 0.0f),
        glm::quat rotation = glm::quat(1.0f, 0.0f, 0.0f, 0.0f),
        glm::vec3 scale = glm::vec3(1.0f, 1.0f, 1.0f)
    );

};

#endif //CG2_MESHCLASS_H