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

    void Vec3f::SphereToCartesian(float alpha, float beta, float radius) {
            SetX(radius * cos(beta) * sin(alpha));
            SetY(radius * sin(beta));
            SetZ(radius * cos(beta) * cos(alpha));
    }

    Vec3f Vec3f::CreateCartesianFromSphere(float alpha, float beta, float radius) {
        Vec3f res;
        res.SphereToCartesian(alpha, beta, radius);
        return res;
    }

    std::ostream &operator<<(std::ostream &os, const Vec3f& vec3F) {
        os << vec3F.GetX() << ' ' << vec3F.GetY() << ' ' << vec3F.GetZ();
        return os;
    }

} // cg_math