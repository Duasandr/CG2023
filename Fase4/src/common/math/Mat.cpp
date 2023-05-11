//
// Created by Sandro Duarte on 24/04/2023.
//

#include "Mat.h"

namespace cg_math {
    using std::initializer_list;
    using std::vector;
    using std::make_shared;

    /*
    * //////////////////////////////
    * // Constructors
    * //////////////////////////////
    */

    Mat::Mat() : mRows(0), mCols(0) { mSharedFloatVector = nullptr; }

    Mat::Mat(uint32_t rows, uint32_t cols) : mRows(rows), mCols(cols) {
        mSharedFloatVector = make_shared<vector<float>>(rows * cols);
        std::fill(mSharedFloatVector->begin(), mSharedFloatVector->end(), 0.0f);
    }

    Mat::Mat(const Vec3f &vec) : Mat(1, 4) {
        Set(0, vec.GetX());
        Set(1, vec.GetY());
        Set(2, vec.GetZ());
        Set(3, 1.0f);
    }

    Mat::Mat(uint32_t rows, uint32_t cols, initializer_list<float> list) : Mat(rows, cols) {
        std::copy(list.begin(), list.end(), mSharedFloatVector->begin());
    }

    Mat::Mat(uint32_t rows, uint32_t cols, std::vector<float> vec) : Mat(rows, cols) {
        std::copy(vec.begin(), vec.end(), mSharedFloatVector->begin());
    }

    /*
     * //////////////////////////////
     * // Static Methods
     * //////////////////////////////
     */

    void Mat::Multiply(const Mat &lhs, const Mat &rhs, Mat &res) {
        const uint32_t rows = lhs.mRows;
        const uint32_t cols = rhs.mCols;

        for (uint32_t i = 0; i < rows; ++i) {
            for (uint32_t j = 0; j < cols; ++j) {
                float sum = 0.0f;
                for (uint32_t k = 0; k < cols; ++k) {
                    float value = lhs.Get(i, k) * rhs.Get(k, j);
                    sum += value;
                }
                res.Set(i, j, sum);
            }
        }
    }

    Mat Mat::Multiply(const Mat &lhs, const Mat &rhs) {
        if (lhs.mCols != rhs.mRows) {
            throw std::invalid_argument("Matrices cannot be multiplied");
        }
        Mat res(lhs.GetRows(), rhs.GetCols());
        Multiply(lhs, rhs, res);
        return res;
    }

    Mat Mat::Multiply(const Mat &mat, const Vec3f &vec) {
        Mat res(mat.GetRows(), 1);
        Mat rhs(vec);
        Multiply(mat, rhs, res);
        return res;
    }

    Mat Mat::Transpose(const Mat &mat) {
        Mat res(mat.mCols, mat.mRows);

        for (uint32_t i = 0; i < mat.mRows; ++i) {
            for (uint32_t j = 0; j < mat.mCols; ++j) {
                res.Set(j, i, mat.Get(i * mat.mCols + j));
            }
        }

        return res;
    }

    /*
     * //////////////////////////////
     * // Setters
     * //////////////////////////////
     */

    void Mat::Set(uint32_t index, float value) { mSharedFloatVector->at(index) = value; }

    void Mat::Set(uint32_t row, uint32_t col, float value) {
        uint32_t index = row * mRows + col;
        Set(index, value);
    }

    /*
     * //////////////////////////////
     * // Getters
     * //////////////////////////////
     */

    float Mat::Get(uint32_t index) const { return mSharedFloatVector->at(index); }

    float Mat::Get(uint32_t row, uint32_t col) const {
        uint32_t index = row * mRows + col;
        return Get(index);
    }

    uint32_t Mat::GetRows() const { return mRows; }
    uint32_t Mat::GetCols() const { return mCols; }

    Mat Mat::RotationMatrix(const Vec3f &x, const Vec3f &y, const Vec3f &z) {
        Mat res(4,4, {x.GetX(), x.GetY(), x.GetZ(), 0,
                                    y.GetX(), y.GetY(), y.GetZ(), 0,
                                    z.GetX(), z.GetY(), z.GetZ(), 0,
                                    0, 0, 0, 1});

        return res;
    }

    float *Mat::GetData() const { return mSharedFloatVector->data(); }


    /*
     * //////////////////////////////
     * // Overloaded Operators
     * //////////////////////////////
     */

    Mat operator*(const Mat &lhs, const Mat &rhs)              { return Mat::Multiply(lhs, rhs); }
    Mat operator*(const Mat &mat, const Vec3f &vec)            { return Mat::Multiply(mat, vec); }

    std::ostream &operator<<(std::ostream &os, const Mat &mat) {
        for (uint32_t i = 0; i < mat.GetRows(); ++i) {
            for (uint32_t j = 0; j < mat.GetCols(); ++j) {
                os << mat.Get(i, j) << " ";
            }
            os << std::endl;
        }
        return os;
    }


} // math
