//
// Created by Sandro Duarte on 15/05/2023.
//
#ifdef __APPLE__
#include <glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif
#include "world/lights/PointLight.h"

PointLight::PointLight(float x, float y, float z) : Light() {
    mPosition[0] = x;
    mPosition[1] = y;
    mPosition[2] = z;
    mPosition[3] = 1;
}

void PointLight::TurnOn() {
    glLightfv(mId, GL_POSITION, mPosition);
}

