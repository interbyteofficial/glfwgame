#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include "shader.h"

using namespace std;

Shader::Shader()
{

}

Shader::~Shader()
{

}

Shader::Shader(char* path_vertex,char* path_fragment)
{
    loadShader(path_vertex,path_fragment);
}

bool Shader::loadShader(char* path_vertex,char* path_fragment)
{
    GLuint shaderid, vertexid, fragmentid;
    string code_vertex, code_fragment;
    ifstream file_vertex, file_fragment;

    file_vertex.open(path_vertex);
    stringstream ssvertex;
    ssvertex << file_vertex.rdbuf();
    code_vertex = ssvertex.str();
    file_vertex.close();
    if(code_vertex.size()==0){
        cout<<"ERROR: SHADER LOAD ERROR\n File \""<<path_vertex<<"\" is empty!\n"<<endl;
    }

    file_fragment.open(path_fragment);
    stringstream ssfragment;
    ssfragment << file_fragment.rdbuf();
    code_fragment = ssfragment.str();
    file_fragment.close();
    if(code_fragment.size()==0){
        cout<<"ERROR: SHADER LOAD ERROR\n File \""<<path_fragment<<"\" is empty!\n"<<endl;
    }

    const char* buffer_vertex = code_vertex.c_str();
    vertexid = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexid, 1, &buffer_vertex, NULL);
    glCompileShader(vertexid);
    GLint success;
    GLchar infolog[1024];
    glGetShaderiv(vertexid, GL_COMPILE_STATUS, &success);
    if(!success){
        glGetShaderInfoLog(vertexid, 1024, NULL, infolog);
        cout<<"SHADER ERROR: Failed to compile vertex shader "<<path_vertex<<"\n"<<infolog<<endl;
        return false;
    }

    const char* buffer_fragment = code_fragment.c_str();
    fragmentid = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentid, 1, &buffer_fragment, NULL);
    glCompileShader(fragmentid);
    glGetShaderiv(fragmentid, GL_COMPILE_STATUS, &success);
    if(!success){
        glGetShaderInfoLog(fragmentid, 1024, NULL, infolog);
        cout<<"SHADER ERROR: Failed to compile fragment shader "<<path_fragment<<"\n"<<infolog<<endl;
        return false;
    }

    id = glCreateProgram();
    glAttachShader(id, vertexid);
    glAttachShader(id, fragmentid);
    glLinkProgram(id);

    glDeleteShader(vertexid);
    glDeleteShader(fragmentid);
}

void Shader::use()
{
    glUseProgram(id);
}

GLuint Shader::getId(){
    return id;
}
