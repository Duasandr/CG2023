//
// Created by Sandro Duarte on 19/03/2023.
//
#ifdef __APPLE__
#include <glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif
#include "transform/Rotate.h"

namespace cg_engine {
    using cg_math::Vec3f;

    Rotate::Rotate(float angle, float x, float y, float z) {
        mVector = Vec3f(x, y, z);
        mAngle = angle;
    }

    void Rotate::Apply() {
        glRotatef(mAngle, mVector.GetX(), mVector.GetY(), mVector.GetZ());
    }
} // cg_engine