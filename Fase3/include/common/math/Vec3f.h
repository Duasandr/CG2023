//
// Created by Sandro Duarte on 09/03/2023.
//

#ifndef COMMON_VEC3F_H
#define COMMON_VEC3F_H
#include <iostream>
#include <cmath>

namespace cg_math {
    class Mat;
    /**
     * @brief Vec3f class.
     * @details It represents a 3D vector.
     */
    class Vec3f {
    public:
        /*
         * //////////////////////////////
         * // Friend functions
         * //////////////////////////////
         */

        // We use friend functions to access private members of the class.

        friend std::ostream& operator<<(std::ostream& os, const Vec3f& vec);

        friend Vec3f operator+(const Vec3f& lhs, const Vec3f& rhs);
        friend Vec3f operator-(const Vec3f& lhs, const Vec3f& rhs);
        friend Vec3f operator*(const Vec3f& lhs, const Vec3f& rhs);

        friend Vec3f operator+(const Vec3f& vec, float scalar);
        friend Vec3f operator-(const Vec3f& vec, float scalar);
        friend Vec3f operator*(const Vec3f& vec, float scalar);



        /*
         * //////////////////////////////
         * // Constructors and destructor
         * //////////////////////////////
         */

        /**
         * @brief Default constructor.
         * @details Sets x, y and z to 0. (0, 0, 0)
         */
        Vec3f();
        /**
         * @brief Parameter constructor.
         * @details Sets x, y and z to the given values. (x, y, z)
         * @param x value of x
         * @param y value of y
         * @param z value of z
         */
        Vec3f(float x, float y, float z);
        /**
         * @brief Copy constructor.
         * @details Sets x, y and z to the values of the given vector.
         * @param vec vector to copy
         */
        Vec3f(const Vec3f& vec);
        /**
         * @brief Parameter constructor.
         * @details Sets x, y and z to the values of the given vector.
         * Useful for converting from other types of vectors and achieving polymorphism.
         * Explicit is used to avoid implicit conversions, this means that the compiler
         * will not automatically convert from one type to another.
         * E.g. Vec3f vec = {1, 2, 3} will not work but Vec3f vec({1, 2, 3}) will work.
         * @param vec vector to copy
         */
        explicit Vec3f(std::vector<float> &vec);

        /**
         * @brief Default destructor.
         * @details Destructor is defaulted because the compiler can
         * generate a destructor for us since it is a trivial class.
         */
        virtual ~Vec3f() = default;

        /*
         * //////////////////////////////
         * // Static methods
         * //////////////////////////////
         */

        /**
         * Returns the norm (length) of the vector.
         * @details The norm is the square root of the sum of the squares of the components of the vector.
         * @param vec vector to get the norm
         * @return float length of the vector
        */
        static float Norm       (const Vec3f& vec);
        /**
         * @brief Returns the distance between two vectors.
         * @details The distance is the norm of the difference between the two vectors.
         * @param lhs left hand side vector
         * @param rhs right hand side vector
         * @return float distance between the two vectors
         */
        static float Distance   (const Vec3f& lhs, const Vec3f& rhs);
        /**
         * Returns a normalized vector.
         * @details The normalized vector has the same direction as the original vector, but its length is 1.
         * All components of the vector are divided by the norm of the vector.
         * @param vec vector to normalize
         * @return Vec3f normalized vector
         */
        static Vec3f Normalize  (const Vec3f& vec);
        /**
         * Returns the dot product of two vectors.
         * @param lhs first vector
         * @param rhs second vector
         * @return float dot product
         */
        static Vec3f Cross      (const Vec3f& lhs, const Vec3f& rhs);

        /**
         * Returns the dot product of two vectors.
         * @param lhs first vector
         * @param rhs second vector
         * @return float dot product
         */
        static float Dot      (const Vec3f& lhs, const Vec3f& rhs);

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

        /*
         * //////////////////////////////
         * // Setters
         * //////////////////////////////
         */

        /**
         * @brief Sets the x component of the vector.
         * @param x value to set
         */
        void SetX   (float x);
        /**
         * @brief Sets the y component of the vector.
         * @param y value to set
         */
        void SetY   (float y);
        /**
         * @brief Sets the z component of the vector.
         * @param z value to set
         */
        void SetZ   (float z);

        /**
         * @brief Sets the x, y and z components of the vector.
         * @param x value to set
         * @param y value to set
         * @param z value to set
         */
        void Set    (float x, float y, float z);
        /**
         * @brief Sets the x, y and z components of the vector.
         * @param vec vector to copy
         */
        void Set    (const Vec3f& vec);
        /**
         * @brief Sets the x, y and z components of the vector.
         * @param vec vector to copy
         */
        void Set    (const std::vector<float> &vec);

        /*
         * //////////////////////////////
         * // Getters
         * //////////////////////////////
         */

        /**
         * @brief Returns the x component of the vector.
         * @return x value
         */
        float GetX() const;
        /**
         * @brief Returns the y component of the vector.
         * @return y value
         */
        float GetY() const;
        /**
         * @brief Returns the z component of the vector.
         * @return z value
         */
        float GetZ() const;


        /*
         * //////////////////////////////
         * // Overloaded instance operators
         * //////////////////////////////
         */

        /**
         * @brief Overload of the -= operator.
         * @details Subtracts the rhs vector.
         * @param rhs vector to subtract
         * @return reference to the this vector now with the subtraction applied
         */
        Vec3f &operator-=(const Vec3f& rhs);
        /**
         * @brief Overload of the += operator.
         * @details Adds the rhs vector.
         * @param rhs vector to add
         * @return reference to the this vector now with the addition applied
         */
        Vec3f &operator+=(const Vec3f& rhs);

    private:
        /*
         * //////////////////////////////
         * // Private instance methods
         * //////////////////////////////
         */

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

        /*
         * //////////////////////////////
         * // Private instance variables
         * //////////////////////////////
         */

        // x component of the vector
        float mX;
        // y component of the vector
        float mY;
        // z component of the vector
        float mZ;
    };

    /*
    * //////////////////////////////
    * // Overloaded global operators
    * //////////////////////////////
    */

    // We use the global operators to avoid having to overload the operators for every type of vector.
    // For example, if we had a Vec3i, we would have to overload the operators for Vec3i and Vec3f.
    // With the global operators, we only have to overload the operators for Vec3f and we can use them
    // with any type of vector.
    // The downside is that we have to pass the vectors as const references, which is not ideal.
    // However, we can use the move constructor to avoid copying the vectors.
    // For example, if we have a function that takes a Vec3f as a parameter, we can call it with
    // a temporary vector, which will be moved to the function parameter.
    // This way, we avoid copying the vector.
    // For example:
    // Vec3f vec(1, 2, 3);
    // Vec3f vec2 = vec + Vec3f(1, 2, 3);
    // In this case, the vector Vec3f(1, 2, 3) will be moved to the function parameter, avoiding a copy.
    // If we had overloaded the operators for Vec3f and Vec3i, we would have to pass the vectors as
    // const references, which would be less efficient.
    // For example:
    // Vec3f vec(1, 2, 3);
    // Vec3i vec2(1, 2, 3);
    // Vec3f vec3 = vec + vec2;
    // In this case, we would have to pass the vectors as const references, which would be less efficient.
    // However, we can still use the move constructor to avoid copying the vectors.
    // For example:
    // Vec3f vec(1, 2, 3);
    // Vec3i vec2(1, 2, 3);
    // Vec3f vec3 = vec + std::move(vec2);
    // In this case, the vector vec2 will be moved to the function parameter, avoiding a copy.

        /*
         * //////////////////////////////
         * // Stream operators
         * //////////////////////////////
        */

    /**
     * @brief Overload of the << operator.
     * @details Prints the vector to the given stream. Mainly used for debugging or logging.
     * @param os stream to print to
     * @param vec vector to print
     * @return reference to the stream with the vector printed
    */
    std::ostream &operator<<(std::ostream &os, const Vec3f& vec);

    /**
     * @brief Overload of the >> operator.
     * @details Builds the vector from a given stream.
     * @param is stream to read from
     * @param vec vector to build
     * @return reference to the stream with the vector was read from.
    */
    std::istream &operator>>(std::istream &is, Vec3f& vec);

        /*
        * //////////////////////////////
        * // Arithmetic operators
        * //////////////////////////////
        */

            /*
            * //////////////////////////////
            * // Arithmetic operators with vectors
            * //////////////////////////////
            */

    /**
     * @brief Overload of the + operator.
     * @details Adds the two vectors. (x1 + x2, y1 + y2, z1 + z2)
     * @param lhs left hand side vector
     * @param rhs right hand side vector
     * @return Vec3f vector with the addition applied. The original vectors are not modified.
     */
    Vec3f operator+   (const Vec3f& lhs, const Vec3f& rhs);
    /**
     * @brief Overload of the - operator.
     * @details Subtracts the two vectors. (x1 - x2, y1 - y2, z1 - z2)
     * @param lhs left hand side vector
     * @param rhs right hand side vector
     * @return Vec3f vector with the subtraction applied. The original vectors are not modified.
     */
    Vec3f operator-   (const Vec3f& lhs, const Vec3f& rhs);
    /**
     * @brief Overload of the * operator.
     * @details Multiplies the two vectors. (x1 * x2, y1 * y2, z1 * z2)
     * @param lhs left hand side vector
     * @param rhs right hand side vector
     * @return Vec3f vector with the multiplication applied. The original vectors are not modified.
     */
    Vec3f operator*   (const Vec3f& lhs, const Vec3f& rhs);

            /*
            * //////////////////////////////
            * // Arithmetic operators with scalars
            * //////////////////////////////
            */

    /**
     * @brief Overload of the + operator.
     * @details Adds the scalar to the vector. (x + scalar, y + scalar, z + scalar)
     * @param vec vector to add the scalar to
     * @param scalar scalar to add
     * @return Vec3f vector with the addition applied. The original vector is not modified.
     */
    Vec3f operator+   (const Vec3f& vec, float scalar);
    /**
     * @brief Overload of the - operator.
     * @details Subtracts the scalar from the vector. (x - scalar, y - scalar, z - scalar)
     * @param vec vector to subtract the scalar from
     * @param scalar scalar to subtract
     * @return Vec3f vector with the subtraction applied. The original vector is not modified.
     */
    Vec3f operator-   (const Vec3f& vec, float scalar);
    /**
     * @brief Overload of the * operator.
     * @details Multiplies the vector by the scalar. (x * scalar, y * scalar, z * scalar)
     * @param vec vector to multiply
     * @param scalar scalar to multiply by
     * @return Vec3f vector with the multiplication applied. The original vector is not modified.
     */
    Vec3f operator*   (const Vec3f& vec, float scalar);
} // math

#endif //COMMON_VEC3F_H
