//
// Created by Sandro Duarte on 15/05/2023.
//
#ifdef __APPLE__
#include <glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif
#include "world/lights/SpotLight.h"

SpotLight::SpotLight(float px, float py, float pz, float dx, float dy, float dz, float cutOff) : Light() {
    mPosition[0] = px;
    mPosition[1] = py;
    mPosition[2] = pz;
    mPosition[3] = 1;

    mDirection[0] = dx;
    mDirection[1] = dy;
    mDirection[2] = dz;
    mDirection[3] = 0;

    mCutOff = cutOff;

}

void SpotLight::TurnOn() {
    glLightfv(mId, GL_POSITION, mPosition);
    glLightfv(mId, GL_SPOT_DIRECTION, mDirection);
    glLightfv(mId, GL_SPOT_CUTOFF, &mCutOff);
}
