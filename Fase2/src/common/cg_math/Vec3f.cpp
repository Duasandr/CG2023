//
// Created by Sandro Duarte on 09/03/2023.
//

#include <vector>
#include "Vec3f.h"

/**
 * @brief cg_math namespace contains all the math classes and functions.
 */
namespace cg_math {
    using std::vector;
    using std::pow;
    using std::sqrt;

    /*
    * //////////////////////////////
    * // Constructors
    * //////////////////////////////
    */

    Vec3f::Vec3f()                          : mX(0), mY(0), mZ(0) {}
    Vec3f::Vec3f(float x, float y, float z) : mX(x), mY(y), mZ(z) {}
    Vec3f::Vec3f(const Vec3f &vec)          : Vec3f() { Set(vec); }
    Vec3f::Vec3f(vector<float> &vec)        : Vec3f() {
        if (vec.size() < 3) {
            throw std::invalid_argument("Vector must have at least 3 elements.");
        }
        Set(vec);
    }

    /*
    * //////////////////////////////
    * // Static methods
    * //////////////////////////////
    */

    Vec3f Vec3f::CreateCartesianFromPolar(float alpha, float height, float radius) {
        float x = radius * cos(alpha);
        float z = radius * sin(alpha);

        return {x, height, z};
    }

    Vec3f Vec3f::CreateCartesianFromSphere(float alpha, float beta, float radius) {
        float x = radius * cos(beta) * sin(alpha);
        float y = radius * sin(beta);
        float z = radius * cos(beta) * cos(alpha);

        return {x, y, z};
    }

    float Vec3f::Norm(const Vec3f &vec) {
        // We use double precision to be consistent with the sqrt and pow functions
        double delta = pow(vec.GetX(), 2) + pow(vec.GetY(), 2) + pow(vec.GetZ(), 2);

        // Handle negative numbers due to floating point precision
        if (delta < 0) { return 0; }

        // We return from a static cast to float to be consistent with the rest of the code
        // Also the loss of precision is not a problem
        return static_cast<float>(sqrt(delta));
    }

    Vec3f Vec3f::Normalize(const Vec3f &vec) {
        float norm = Norm(vec);

        // Handle the case where the norm is 0 and avoid division by 0
        // We return a vector with all 0s
        if (norm == 0) { return {0,0,0}; }

        return {vec.GetX() / norm, vec.GetY() / norm, vec.GetZ() / norm };
    }

    Vec3f Vec3f::Cross(const Vec3f &lhs, const Vec3f &rhs) {
        float x = lhs.GetY() * rhs.GetZ() - lhs.GetZ() * rhs.GetY();
        float y = lhs.GetZ() * rhs.GetX() - lhs.GetX() * rhs.GetZ();
        float z = lhs.GetX() * rhs.GetY() - lhs.GetY() * rhs.GetX();

        return {x, y, z};
    }

    /*
    * //////////////////////////////
    * // Setters
    * //////////////////////////////
    */

    void Vec3f::SetX(float x)                   { mX = x; }
    void Vec3f::SetY(float y)                   { mY = y; }
    void Vec3f::SetZ(float z)                   { mZ = z; }
    void Vec3f::Set (float x, float y, float z) {
        // We use the setters for sake of consistency
        SetX(x);
        SetY(y);
        SetZ(z);
    }

    void Vec3f::Set (const Vec3f &vec) {
        Set(vec.GetX(), vec.GetY(), vec.GetZ());
    }

    void Vec3f::Set (const vector<float> &vec) {
        Set(vec[0], vec[1], vec[2]);
    }

    /*
    * //////////////////////////////
    * // Getters
    * //////////////////////////////
    */

    float Vec3f::GetX() const { return mX; }
    float Vec3f::GetY() const { return mY; }
    float Vec3f::GetZ() const { return mZ; }

    /*
    * //////////////////////////////
    * // Instance methods
    * //////////////////////////////
    */

    void Vec3f::SphereToCartesian(float alpha, float beta, float radius) {
        float x = radius * cos(beta) * sin(alpha);
        float y = radius * sin(beta);
        float z = radius * cos(beta) * cos(alpha);

        Set(x, y, z);
    }

    void Vec3f::PolarToCartesian(float alpha, float height, float radius) {
        float x = radius * cos(alpha);
        float z = radius * sin(alpha);

        Set(x, height, z);
    }



    /*
    * //////////////////////////////
    * // Overloaded operators
    * //////////////////////////////
    */

    /*
    * //////////////////////////////
    * // Instance operators
    * //////////////////////////////
    */

    Vec3f &Vec3f::operator-=(const Vec3f &rhs) {
        Set(GetX() - rhs.GetX(), GetY() - rhs.GetY(), GetZ() - rhs.GetZ());
        return *this;
    }

    Vec3f &Vec3f::operator+=(const Vec3f &rhs) {
        Set(GetX() + rhs.GetX(), GetY() + rhs.GetY(), GetZ() + rhs.GetZ());
        return *this;
    }

    /*
    * //////////////////////////////
    * // Global Overloaded operators
    * //////////////////////////////
    */

    std::ostream &operator<<(std::ostream &os, const Vec3f& vec) {
        return  os << vec.GetX() << ' ' << vec.GetY() << ' ' << vec.GetZ();
    }

    Vec3f operator+(const Vec3f& lhs, const Vec3f& rhs) {
        float x = lhs.GetX() + rhs.GetX();
        float y = lhs.GetY() + rhs.GetY();
        float z = lhs.GetZ() + rhs.GetZ();

        return {x, y, z};
    }


    Vec3f operator+(const Vec3f& vec, float scalar) {
        float x = vec.GetX() + scalar;
        float y = vec.GetY() + scalar;
        float z = vec.GetZ() + scalar;

        return {x, y, z};
    }

    Vec3f operator-(const Vec3f& lhs, const Vec3f& rhs) {
        // We use the + operator to avoid code duplication
        return operator+(lhs, rhs * (-1));
    }

    Vec3f operator-(const Vec3f& vec, float scalar) {
        // We use the + operator to avoid code duplication
        return operator+(vec, -scalar);
    }

    Vec3f operator*(const Vec3f& lhs, const Vec3f& rhs) {
        float x = lhs.GetX() * rhs.GetX();
        float y = lhs.GetY() * rhs.GetY();
        float z = lhs.GetZ() * rhs.GetZ();

        return {x, y, z};
    }

    Vec3f operator*(const Vec3f& vec, float scalar) {
        float x = vec.GetX() * scalar;
        float y = vec.GetY() * scalar;
        float z = vec.GetZ() * scalar;

        return {x, y, z};
    }
} // cg_math