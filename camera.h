#ifndef CAMERA_H_INCLUDED
#define CAMERA_H_INCLUDED

#define GLEW_STATIC
#include <GL/glew.h>
#include <iostream>
#include <GLFW/glfw3.h>
#include <glm/common.hpp>
#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>

using namespace std;
using namespace glm;

class Camera
{
private:
    vec3 position;
    vec3 rotation;
    vec3 forward;

    mat4 projection;
    mat4 view;

    GLfloat lastmx,lastmy;
    float anglex,angley;
    bool keys[3];
public:
    Camera();
    Camera(float fov,int width,int height,float near,float far);
    void setPerspective(float fov,int width,int height,float near,float far);
    void setPosition(vec3 position);
    void setRotation(vec3 rotation);
    void setView(vec3 position,vec3 rotation);
    void update();
    static void handleMouse(GLFWwindow* window, int key, int scancode, int action, int mods);

    mat4 getProjMatrix();
    mat4 getViewMatrix();
};

#endif // CAMERA_H_INCLUDED
