//
// Created by Sandro Duarte on 09/03/2023.
//

#ifndef ENGINE_VEC3F_H
#define ENGINE_VEC3F_H
#define _USE_MATH_DEFINES
#include <iostream>
#include <cmath>


namespace cg_math {

    /**
     * Represents a vector of three floats
     */
    class Vec3f {
    public:
        Vec3f();
        Vec3f(float x, float y, float z);
        virtual ~Vec3f();

        static Vec3f CreateCartesianFromSphere(float alpha, float beta , float radius);

        void SphereToCartesian(float alpha, float beta, float radius);

        /**
         * Sets x value.
         * @param x
         */
        void SetX(float x);

        /**
         * Sets y value.
         * @param y
         */
        void SetY(float y);

        /**
         * Sets z value.
         * @param z
         */
        void SetZ(float z);

        /**
         * Gets x value.
         * @return x
         */
        float GetX() const;

        /**
         * Gets y value.
         * @return
         */
        float GetY() const;

        /**
         * Gets z value.
         * @return
         */
        float GetZ() const;

    private:
        float mX;
        float mY;
        float mZ;
    };

    std::ostream &operator<<(std::ostream &os, const Vec3f& vec3F);
} // cg_math

#endif //ENGINE_VEC3F_H
