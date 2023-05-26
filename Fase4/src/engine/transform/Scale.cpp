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

    Scale::Scale() {
        mFactor = 1.0f;
        mScaleVec = nullptr;
    }

    Scale::Scale(float factor) {
        mFactor = factor;
        mScaleVec = nullptr;
    }

    void Scale::Apply() {
        if(mScaleVec != nullptr) {
            glScalef(mScaleVec->GetX(), mScaleVec->GetY(), mScaleVec->GetZ());
        }else{
            glScalef(mFactor, mFactor, mFactor);
        }
    }

    Scale::Scale(float x, float y, float z) {
        mFactor = 1;
        mScaleVec = new Vec3f(x,y,z);
    }

} // cg_engine