//
// Created by Sandro Duarte on 24/04/2023.
//

#include "Mat.h"

namespace cg_math {
    Mat::Mat() : mRows(0), mCols(0) { mData = nullptr; }

    Mat::Mat(uint32_t rows, uint32_t cols) : mRows(rows), mCols(cols) {
        mData = new float[rows * cols];
        std::fill(mData, mData + rows * cols, 0);
    }

    Mat::Mat(uint32_t rows, uint32_t cols, float *data) : mRows(rows), mCols(cols) {
        mData = new float[rows * cols];
        std::copy(data, data + rows * cols, mData);
    }

    Mat::Mat(const Vec3f &vec) : Mat(4, 1) {
        mData[0] = vec.GetX();
        mData[1] = vec.GetY();
        mData[2] = vec.GetZ();
        mData[3] = 1;
    }

    Mat::~Mat() {
        Destroy();
    }

    Mat Mat::Multiply(const Mat &lhs, const Mat &rhs) {
        Mat res(lhs.mRows, rhs.mCols);

        for (uint32_t i = 0; i < lhs.mRows; ++i) {
            for (uint32_t j = 0; j < rhs.mCols; ++j) {
                for (uint32_t k = 0; k < lhs.mCols; ++k) {
                    res.mData[i * rhs.mCols + j] += lhs.mData[i * lhs.mCols + k] * rhs.mData[k * rhs.mCols + j];
                }
            }
        }

        return res;
    }

    Mat Mat::Multiply(const Mat &mat, const Vec3f &vec) {
        return Multiply(mat, Mat(vec));
    }

    Mat Mat::Transpose(const Mat &mat) {
        Mat res(mat.mCols, mat.mRows);

        for (uint32_t i = 0; i < mat.mRows; ++i) {
            for (uint32_t j = 0; j < mat.mCols; ++j) {
                res.mData[j * mat.mRows + i] = mat.mData[i * mat.mCols + j];
            }
        }

        return res;
    }

    void Mat::Destroy() {
        if (mData != nullptr){

        }
    }

    Mat::Mat(std::initializer_list<float> list) {
        mRows = 1;
        mCols = list.size();
        mData = new float[mRows];
        std::copy(list.begin(), list.end(), mData);
    }

    Mat::Mat(std::initializer_list<std::initializer_list<float>> list) {
        mRows = list.size();
        mCols = list.begin()->size();
        mData = new float[mRows * mCols];

        uint32_t i = 0;
        for (auto &row : list) {
            std::copy(row.begin(), row.end(), mData + i * mCols);
            ++i;
        }
    }

    float Mat::Get(uint32_t row, uint32_t col) const {
        return mData[row * mCols + col];
    }

    Mat operator*(const Mat &lhs, const Mat &rhs) {
        return Mat::Multiply(lhs, rhs);
    }

    Mat operator*(const Mat &mat, const Vec3f &vec) {
        return Mat::Multiply(mat, vec);
    }


} // math