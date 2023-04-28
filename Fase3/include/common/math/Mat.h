//
// Created by Sandro Duarte on 24/04/2023.
//

#ifndef COMMON_MAT_H
#define COMMON_MAT_H

#include <vector>
#include "Vec3f.h"

namespace cg_math {
    class Mat {
    public:
        static const Mat BezierMatrix;

        Mat();
        Mat(uint32_t rows, uint32_t cols);
        Mat(uint32_t rows, uint32_t cols, float *data);
        Mat(std::initializer_list<float> list);
        Mat(std::initializer_list<std::initializer_list<float>> list);
        explicit Mat(const cg_math::Vec3f &vec);
        ~Mat();

        static Mat Multiply(const Mat &lhs, const Mat &rhs);
        static Mat Multiply(const Mat &mat, const Vec3f &vec);
        static Mat Transpose(const Mat &mat);

        void Destroy();
        float Get(uint32_t row, uint32_t col) const;

    private:
        uint32_t mRows;
        uint32_t mCols;
        float* mData;
    };

    Mat operator*(const Mat &lhs, const Mat &rhs);
    Mat operator*(const Mat &mat, const Vec3f &vec);
} // math

#endif //COMMON_MAT_H
