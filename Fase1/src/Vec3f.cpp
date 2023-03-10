//
// Created by Sandro Duarte on 09/03/2023.
//

#include "Vec3f.h"

namespace cg_math {
    Vec3f::Vec3f() {
        mX =  mY = mZ = 0;
    }

    Vec3f::Vec3f(float x, float y, float z) {
        mX = x;
        mY = y;
        mZ = z;
    }

    Vec3f::~Vec3f() {

    }

    void Vec3f::SetX(float x) {
        mX = x;
    }

    void Vec3f::SetY(float y) {
        mY = y;
    }

    void Vec3f::SetZ(float z) {
        mZ = z;
    }

    float Vec3f::GetX() const {
        return mX;
    }

    float Vec3f::GetY() const {
        return mY;
    }

    float Vec3f::GetZ() const {
        return mZ;
    }

} // cg_math