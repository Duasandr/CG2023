//
// Created by Sandro Duarte on 19/03/2023.
//
#ifdef __APPLE__
#include <glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif
#include "transform/Scale.h"

namespace cg_engine {
    using cg_math::Vec3f;

    Scale::Scale() { mFactor = 1.0f; }

    Scale::Scale(float factor) { mFactor = factor; }

    void Scale::Apply() { glScalef(mFactor, mFactor, mFactor); }

} // cg_engine