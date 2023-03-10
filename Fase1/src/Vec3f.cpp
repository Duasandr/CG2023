//
// Created by Sandro Duarte on 09/03/2023.
//

#include "Vec3f.h"

namespace cg_math {
    Vec3f::Vec3f() {
        mX =  mY = mZ = 0;
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

    float Vec3f::GetX() {
        return mX;
    }

    float Vec3f::GetY() {
        return mY;
    }

    float Vec3f::GetZ() {
        return mZ;
    }

} // cg_math