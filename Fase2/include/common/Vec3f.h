//
// Created by Sandro Duarte on 09/03/2023.
//

#ifndef ENGINE_VEC3F_H
#define ENGINE_VEC3F_H
#include <iostream>
#include <cmath>


namespace cg_math {

    /**
     * Represents a vector of three floats
     */
    class Vec3f {
    public:
        /**
         * @brief Default constructor.
         * @details Sets x, y and z to 0.
         */
        Vec3f();
        /**
         * @brief Constructor.
         * @details Sets x, y and z to the given values.
         * @param x
         * @param y
         * @param z
         */
        Vec3f(float x, float y, float z);
        /**
         * @brief Default destructor.
         */
        virtual ~Vec3f() = default;

        /**
         * @brief Creates a cartesian vector from spherical coordinates.
         * @param alpha angle in the xy plane
         * @param beta angle in the xz plane
         * @param radius radius of the sphere
         * @return cartesian vector
         */
        static Vec3f CreateCartesianFromSphere(float alpha, float beta , float radius);
        /**
         * @brief Creates a cartesian vector from polar coordinates.
         * @param alpha angle in the xy plane
         * @param height height in the z axis
         * @param radius radius of the circle
         * @return cartesian vector
         */
        static Vec3f CreateCartesianFromPolar(float alpha, float height, float radius);

        /**
         * @brief Converts spherical coordinates to cartesian coordinates.
         * @param alpha angle in the xy plane
         * @param beta angle in the xz plane
         * @param radius radius of the sphere
         */
        void SphereToCartesian(float alpha, float beta, float radius);
        /**
         * @brief Converts polar coordinates to cartesian coordinates.
         * @param alpha angle in the xy plane
         * @param height height in the z axis
         * @param radius radius of the circle
         */
        void PolarToCartesian(float alpha, float height, float radius);

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

        /**
         * Returns the norm (length) of the vector.
         * @return
        */
        float Norm() const;

    private:
        float mX;
        float mY;
        float mZ;
    };

    /**
     * @brief Overload of the << operator.
     * @details Prints the vector in the format x y z.
     * @param os output stream to print to
     * @param vec3F vector to print
     * @return output stream with the vector printed
     */
    std::ostream &operator<<(std::ostream &os, const Vec3f& vec3F);
} // cg_math

#endif //ENGINE_VEC3F_H
