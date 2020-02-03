#define GLEW_STATIC
#include <GL/glew.h>
#include <iostream>
#include <GLFW/glfw3.h>
#include <glm/common.hpp>
#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>
#include <glm/ext/matrix_projection.hpp>
#include <glm/ext/matrix_relational.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "camera.h"

using namespace std;
using namespace glm;

Camera::Camera()
{
    projection = mat4(1.0);
    view = mat4(1.0);
}

Camera::Camera(float fov,int width,int height,float near,float far)
    : Camera()
{
    setPerspective(fov,width,height,near,far);
}

void Camera::setPerspective(float fov,int width,int height,float near,float far)
{
    this->projection = perspective(radians(fov), (float)width/(float)height, near, far);
}

void Camera::update()
{
    this->view = lookAt(position,rotation,vec3(0,1,0));
}

void Camera::setPosition(vec3 position)
{
    this->position=position;
}
void Camera::setRotation(vec3 rotation)
{
    this->rotation=rotation;
}
void Camera::setView(vec3 position,vec3 rotation)
{
    setPosition(position);
    setRotation(rotation);
}

mat4 Camera::getProjMatrix(){
    return projection;
}
mat4 Camera::getViewMatrix(){
    return view;
}
