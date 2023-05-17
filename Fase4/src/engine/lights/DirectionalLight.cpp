//
// Created by Sandro Duarte on 15/05/2023.
//
#ifdef __APPLE__
#include <glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif
#include "world/lights/DirectionalLight.h"

DirectionalLight::DirectionalLight(float x, float y, float z) : Light() {
    mDirection[0] = x;
    mDirection[1] = y;
    mDirection[2] = z;
    mDirection[3] = 0;
}

void DirectionalLight::TurnOn() {
    glLightfv(mId, GL_POSITION, mDirection);
}

