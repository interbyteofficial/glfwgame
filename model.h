#ifndef MODEL_H_INCLUDED
#define MODEL_H_INCLUDED

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/common.hpp>
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>
#include <iostream>
#include "shader.h"
#include "camera.h"

using namespace std;
using namespace glm;

class Vertex
{
private:
    GLuint VAO,VBO,EBO;
    float *vertexbuff;
    int vertexbuff_size;

    unsigned int *elementbuff;
    int elementbuff_size;

    int id;
    string name;

public:
    Vertex();
    Vertex(string name,float vertexbuff[],int vertexbuffsize,unsigned int elementbuff[],int elementbuffsize);
    ~Vertex();

    void render();

    string getName();
    int getId();
};

class Model
{
private:
    GLuint texture;
    Shader shader;
    Vertex vertex;

    vec3 pos;

    string name;
    int id;

public:
    Model();
    Model(string name,Vertex vertex,Shader shader);
    void render();
    void render(Camera *camera);

    void setPosition(vec3 position);
    void setTexture(GLuint texture);
};

#endif // MODEL_H_INCLUDED
