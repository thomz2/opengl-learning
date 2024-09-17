#ifndef MODELCLASS_H
#define MODELCLASS_H

#include <json/njson.h>
#include <vector>
#include "Mesh.h"
#include "Texture.h"
#include "Vertex.h"
#include "shaderClass.h"
#include "Camera.h"

using json = nlohmann::json;
using namespace std;

class Model{
public:
    Model(const char* file);

    void Draw(Shader& shader, Camera& camera);

private:
    const char* file;
    vector<unsigned char> data;
    json JSON;

    vector<Mesh> meshes;
    vector<glm::vec3> translationsMeshes;
    vector<glm::quat> rotationsMeshes;
    vector<glm::vec3> scalesMeshes;
    vector<glm::mat4> matricesMeshes;

    vector<string> loadedTexName;
    vector<Texture> loadedTex;

    void loadMesh(unsigned int indMesh);

    // Traverses a node recursively, so it essentially traverses all connected nodes
    void traverseNode(unsigned int nextNode, glm::mat4 matrix = glm::mat4(1.0f));

    vector<unsigned char> getData();
    vector<float> getFloats(json accessor);
    vector<GLuint> getIndices(json accessor);
    vector<Texture> getTextures();

    vector<Vertex> assembleVertices
    (
        vector<glm::vec3> positions,
        vector<glm::vec3> normals,
        vector<glm::vec2> texUVs
    );

    vector<glm::vec2> groupFloatsVec2(vector<float> floatVec);
    vector<glm::vec3> groupFloatsVec3(vector<float> floatVec);
    vector<glm::vec4> groupFloatsVec4(vector<float> floatVec);
};

#endif