#ifndef VBO_CLASS_H
#define VBO_CLASS_H

#include <glad/glad.h>
#include "../header/Vertex.h"
#include <vector>

using namespace std;

class VBO
{
    public:
        GLuint ID;

        VBO(GLfloat* vertices, GLsizeiptr size);
        VBO(vector<Vertex>& vertices);

        void Bind();
        void Unbind();
        void Delete();
};

#endif