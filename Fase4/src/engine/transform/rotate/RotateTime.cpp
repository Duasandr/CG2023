//
// Created by Sandro Duarte on 26/05/2023.
//
#ifdef __APPLE__
#include <glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif
#include "transform/rotate/RotateTime.h"
using cg_math::Vec3f;

cg_engine::RotateTime::RotateTime() {
    mVector = Vec3f();
    mTime = 0;
    mCurrentAngle = 0;
}

cg_engine::RotateTime::RotateTime(float time, float x, float y, float z) {
    mVector = Vec3f(x,y,z);
    mTime = time;
    mCurrentAngle = 0;
}

void cg_engine::RotateTime::Apply() {
    float delta = glutGet(GLUT_ELAPSED_TIME) / 1000.0f;

    float speed = 360 / mTime; // mTime seconds to complete the curve

    float distance = speed * delta;

    mCurrentAngle += distance;

    if (mCurrentAngle >= 360.0f) {
        // Reset the current angle to zero
        mCurrentAngle = 0;
    }

    glRotatef(distance, mVector.GetX(), mVector.GetY(), mVector.GetZ());
}

