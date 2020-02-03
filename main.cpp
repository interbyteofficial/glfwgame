#define GLEW_STATIC
#define STB_IMAGE_IMPLEMENTATION
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "stb_image.h"
#include <iostream>
#include <windows.h>

#include "shader.h"
#include "model.h"

using namespace std;

GLFWwindow* createWindow(int w, int h, char* title);
GLuint loadTexture(string path);

int main()
{
    //window options
    int wwidth = 512;
    int wheight = 512;
    int bwidth, bheight;
    char* wtitle = "GLFW C++";
    GLFWwindow* window = createWindow(wwidth, wheight, wtitle);
    stbi_set_flip_vertically_on_load(true);

    //render options
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);
    glClearColor(0.53,0.80,0.92,1.0);
    glfwGetFramebufferSize(window, &bwidth, &bheight);
    glViewport(0, 0, bwidth, bheight);

    //objects
//    float vertex[]={
//        0.0,0.0,0.0, 0.0,0.0,
//        0.0,1.0,0.0, 0.0,1.0,
//        1.0,1.0,0.0, 1.0,1.0,
//        1.0,0.0,0.0, 1.0,0.0
//    };
    float vertex[]={
        0.0,0.0,1.0, 0.0,0.0,
        0.0,1.0,1.0, 0.0,1.0,
        1.0,1.0,1.0, 1.0,1.0,
        1.0,0.0,1.0, 1.0,0.0,
    };
    unsigned int vertex_id[]={
        1,2,3,
        1,3,4
    };

    Vertex vertex_test("test",vertex,4*5,vertex_id,6);
    Shader shader_test("main_shader3d.vs","main_shader3d.fs");
//    glUniform1i(glGetUniformLocation(shader_test.getId(), "texture0"), 0);
    Model model_test("test",vertex_test,shader_test);
    model_test.setPosition(vec3(-0.5,-0.5,1));
//    Model model_test2("test",vertex_test,shader_test);
//    model_test2.setPosition(vec3(0,0,-1));
    GLuint texture_test = loadTexture("texture.png");

    //camera
    Camera camera(45,wwidth,wheight,0.1,1000.0);
    camera.setView(vec3(0,0,-1),vec3(0,0,0));

    float x=0;
    //mainloop
    while(!glfwWindowShouldClose(window)){
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        camera.update();
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture_test);
        model_test.render(&camera);
//        model_test2.render(&camera);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}



GLFWwindow* createWindow(int w, int h, char* title)
{
    glfwInit();
    glfwWindowHint(GLFW_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_VERSION_MINOR, 3);
    GLFWwindow* window = glfwCreateWindow(w,h,title,NULL,NULL);
    glfwMakeContextCurrent(window);

    glewExperimental = GL_TRUE;
    glewInit();
    return window;
}

GLuint loadTexture(string path)
{
    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    int w, h, channels;
    unsigned char* buff = stbi_load(path.c_str(), &w, &h, &channels, 0);
    if(buff){
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, buff);
        //glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, buff);
        //glGenerateMipmap(texture);
        return texture;
    }
    else{
        MessageBox(NULL, "FILE_ERROR: Failed to load texture", "Engine error", MB_ICONERROR);
        glDeleteTextures(1, &texture);
        return 0;
    }
}
