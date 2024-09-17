#ifndef LIGHTCLASS_H
#define LIGHTCLASS_H

#include <vector>
#include <string>
#include "Camera.h"
#include "EBO.h"
#include "VAO.h"
#include "Texture.h"
#include "Vertex.h"

using namespace std;

class Light {

public:
    vector <Vertex> vertices;
    vector <GLuint> indices;
    unsigned int type; //0-> pointLight, 1 -> spotLight, 2 -> directional

    VAO vao;

    Light(vector <Vertex>& vertices, vector <GLuint>& indices, unsigned int type);

    void Draw(Shader& shader, Camera& camera);
};

#endif