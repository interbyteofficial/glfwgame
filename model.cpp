#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <glm/common.hpp>
#include <glm/common.hpp>
#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "model.h"
#include "shader.h"
#include "camera.h"

using namespace std;
using namespace glm;

Vertex::Vertex()
{
    glGenBuffers(1, &VBO);
    glGenVertexArrays(1, &VAO);
    glGenVertexArrays(1, &EBO);
}
Vertex::~Vertex()
{

}
Vertex::Vertex(string name,float vertexbuff[],int vertexbuffsize,unsigned int elementbuff[],int elementbuffsize)
    : Vertex()
{
    this->name=name;
    this->vertexbuff=vertexbuff;
    this->vertexbuff_size=vertexbuffsize;
    this->elementbuff=elementbuff;
    this->elementbuff_size=elementbuffsize;

    glBindVertexArray(VAO);
    //set up vbo
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float)*vertexbuffsize,vertexbuff, GL_STATIC_DRAW);
    //set up ebo
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int)*elementbuffsize, elementbuff, GL_STATIC_DRAW);
    //set up vao
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float)*5, 0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float)*5, (void*)(sizeof(float)*3));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Vertex::render()
{
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glDrawElements(GL_TRIANGLES, elementbuff_size, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

Model::Model()
{
    pos = vec3(0.0);
}

Model::Model(string name,Vertex vertex,Shader shader)
{
    this->name = name;
    this->vertex = vertex;
    this->shader = shader;
    pos = vec3(0.0);
}

void Model::render()
{
    if(shader.getId()!=0)
        shader.use();
    vertex.render();
}

void Model::render(Camera *camera)
{
    mat4 MVP = mat4(1.0);
    mat4 modelmat = translate(mat4(1.0),pos);
    MVP = camera->getProjMatrix() * camera->getViewMatrix() * modelmat;
    glUniformMatrix4fv(glGetUniformLocation(shader.getId(), "MVP"), 1, GL_FALSE, &MVP[0][0]);
    if(shader.getId()!=0)
        shader.use();
    vertex.render();
}

void Model::setPosition(vec3 position)
{
    pos = position;
}
