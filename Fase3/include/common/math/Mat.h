//
// Created by Sandro Duarte on 24/04/2023.
//

#ifndef COMMON_MAT_H
#define COMMON_MAT_H

#include <vector>
#include "Vec3f.h"

namespace cg_math {
    /**
     * @brief Matrix class
     * @details This class represents a matrix with a specified number of rows and columns.
     * Provides multiplication of matrices and multiplication of a matrix by a vector.
     */
    class Mat {
    public:
        /*
         * //////////////////////////////
         * // Constructors & Destructor
         * //////////////////////////////
         */

        /**
         * @brief Default constructor
         * @details Creates a matrix with 0 rows and 0 columns
         */
        Mat();

        /**
         * @brief Creates a matrix with the specified number of rows and columns
         * @details Creates a matrix with uninitialized values
         * @param rows The number of rows
         * @param cols The number of columns
         */
        Mat(uint32_t rows, uint32_t cols);

        /**
         * @brief Creates a matrix with the specified number of rows and columns
         * @details Creates a matrix with the values from the initializer list e.g. {1, 2, 3, 4}
         * @param rows The number of rows
         * @param cols The number of columns
         * @param list The initializer list with the values
         */
        Mat(uint32_t rows, uint32_t cols, std::initializer_list<float> list);

        /**
         * @brief Creates a matrix with the specified number of rows and columns
         * @details Creates a matrix with the values from the vector
         * @param rows The number of rows
         * @param cols The number of columns
         * @param vec The vector with the values
         */
        Mat(uint32_t rows, uint32_t cols, std::vector<float> vec);

        /**
         * @brief Creates a matrix from a vector
         * @details Creates a 4 x 1 matrix with the values from the vector
         * @param vec The vector with the values
         */
        explicit Mat(const cg_math::Vec3f &vec);

        /**
         * @brief Default destructor
         */
        ~Mat() = default;

        /*
         * //////////////////////////////
         * // Static Methods
         * //////////////////////////////
         */

        /**
         * @brief Multiplies two matrices and stores the result in the result matrix
         * @details The result matrix must have the same number of rows as the left hand side matrix and the
         * same number of columns as the right hand side matrix
         * @param lhs The left hand side matrix
         * @param rhs The right hand side matrix
         * @param result The result matrix
         */
        static void Multiply(const Mat &lhs, const Mat &rhs, Mat &result);

        /**
         * @brief Multiplies two matrices and returns the result
         * @param lhs Left hand side matrix
         * @param rhs Right hand side matrix
         * @return The result matrix
         */
        static Mat Multiply(const Mat &lhs, const Mat &rhs);

        /**
         * @brief Multiplies a matrix and a vector
         * @param mat The matrix
         * @param vec The vector
         * @param result The result matrix (4 x 1)
         */
        static Mat Multiply(const Mat &mat, const Vec3f &vec);

        /**
         * @brief Transposes a matrix
         * @details The result matrix will be a new matrix
         * @param mat The matrix
         * @return The transposed matrix
         */
        static Mat Transpose(const Mat &mat);

        /**
         * @brief Builds a rotation matrix
         * @param x x-axis
         * @param y y-axis
         * @param z z-axis
         * @return The rotation matrix
         */
        static Mat RotationMatrix(const Vec3f &x, const Vec3f &y, const Vec3f &z);

        /*
         * //////////////////////////////
         * // Setters
         * //////////////////////////////
         */

        /**
         * @brief Sets the value at the specified index
         * @param index index
         * @param value value to set
         */
        void Set(uint32_t index, float value);

        /**
         * @brief Sets the value at the specified row and column
         * @param row row index
         * @param col column index
         * @param value value to set
         */
        void Set(uint32_t row, uint32_t col, float value);

        /*
         * //////////////////////////////
         * // Getters
         * //////////////////////////////
         */

        /**
         * @brief Gets the value at the specified index
         * @param index
         * @return The value at the specified index
         */
        float Get(uint32_t index) const;

        /**
         * @brief Gets the value at the specified row and column
         * @param row
         * @param col
         * @return The value at the specified row and column
         */
        float Get(uint32_t row, uint32_t col) const;

        /**
         * @brief Gets the number of rows
         * @return The number of rows
         */
        uint32_t GetRows() const;

        /**
         * @brief Gets the number of columns
         * @return The number of columns
         */
        uint32_t GetCols() const;

        /**
         * @brief Gets the pointer to the first element in the matrix
         * @return The pointer to the first element in the matrix or nullptr if the matrix is empty
         */
        float *GetData() const;

    private:
        /*
         * //////////////////////////////
         * // Instance Variables
         * //////////////////////////////
         */

        /**
         * @brief The number of rows
         */
        uint32_t mRows;
        /**
         * @brief The number of columns
         */
        uint32_t mCols;
        /**
         * @brief The matrix data
         */
        std::shared_ptr<std::vector<float>> mSharedFloatVector;
    };

    /*
     * //////////////////////////////
     * // Operators
     * //////////////////////////////
     */

    /**
     * @brief Multiplies two matrices and returns the result
     * @param lhs left hand side matrix
     * @param rhs right hand side matrix
     * @return The result matrix
     */
    Mat operator*(const Mat &lhs, const Mat &rhs);

    /**
     * @brief Multiplies a matrix by a vector and returns the result
     * @param mat Left hand side matrix
     * @param vec Right hand side vector
     * @return The result matrix (4 x 1)
     */
    Mat operator*(const Mat &mat, const Vec3f &vec);

    /**
     * @brief Prints the matrix to the output stream
     * @param os output stream
     * @param mat matrix
     * @return The output stream with the matrix printed to it
     */
    std::ostream &operator<<(std::ostream &os, const Mat &mat);

} // math

#endif //COMMON_MAT_H
