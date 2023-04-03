//
// Created by Sandro Duarte on 09/03/2023.
//

#include "Vec3f.h"

/**
 * @brief cg_math namespace contains all the math classes and functions.
 */
namespace cg_math {

    // Constructors

    Vec3f::Vec3f() { mX = mY = mZ = 0; }

    Vec3f::Vec3f(float x, float y, float z) {
        mX = x;
        mY = y;
        mZ = z;
    }

    // Setters and getters

    //Setters

    void Vec3f::SetX(float x) { mX = x; }
    void Vec3f::SetY(float y) { mY = y; }
    void Vec3f::SetZ(float z) { mZ = z; }

    //Getters

    float Vec3f::GetX() const { return mX; }
    float Vec3f::GetY() const { return mY; }
    float Vec3f::GetZ() const { return mZ; }

    float Vec3f::Norm() const {
        return sqrt(mX * mX + mY * mY + mZ * mZ);
    }

    // Static methods

    Vec3f Vec3f::CreateCartesianFromPolar(float alpha, float height, float radius) {
        Vec3f res;
        res.PolarToCartesian(alpha, height, radius);
        return res;
    }

    Vec3f Vec3f::CreateCartesianFromSphere(float alpha, float beta, float radius) {
        Vec3f res;
        res.SphereToCartesian(alpha, beta, radius);
        return res;
    }

    // Non-static methods

    void Vec3f::SphereToCartesian(float alpha, float beta, float radius) {
        SetX(radius * cos(beta) * sin(alpha));
        SetY(radius * sin(beta));
        SetZ(radius * cos(beta) * cos(alpha));
    }

    void Vec3f::PolarToCartesian(float alpha, float height, float radius) {
        SetX(radius * cos(alpha));
        SetY(height);
        SetZ(radius * sin(alpha));
    }

    // Overloaded operators

    std::ostream &operator<<(std::ostream &os, const Vec3f& vec3F) {
        return  os << vec3F.GetX() << ' ' << vec3F.GetY() << ' ' << vec3F.GetZ();
    }

} // cg_math