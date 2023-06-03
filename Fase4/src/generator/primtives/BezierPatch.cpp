//
// Created by Sandro Duarte on 24/04/2023.
//

#include <fstream>
#include "primitives/BezierPatch.h"
#include "Mat.h"
#include "utils/DumpModel.h"

using std::ifstream;
using std::cerr;
using std::cout;
using std::endl;
using cg_math::Vec3f;
using cg_math::Mat;
using std::vector;

/*
         * //////////////////////////////
         * // Static Variables
         * //////////////////////////////
         */

/**
 * @brief The Bezier matrix
 * @details Used to calculate the Bezier curve
 */
static const Mat BezierMatrix(4, 4,
                              {-1, 3, -3, 1,
                                      3, -6, 3, 0,
                                      -3, 3, 0, 0,
                                      1, 0, 0, 0});

/**
 * ////////////////////////////////
 * // Static methods
 * ////////////////////////////////
 */

BezierPatch *BezierPatch::Create(const char *pathToFile, uint32_t tesselation) {
    auto *res = new BezierPatch();

    ifstream ifs(pathToFile);

    // Check if file exists
    if (!ifs.is_open()) {
        cerr << "File " << pathToFile << " not found." << endl;
        return nullptr;
    }

    uint32_t totalPatches;
    ifs >> totalPatches;

    // Read the total number of indices
    uint32_t totalIndices = totalPatches * PATCH_SIZE;
    uint32_t indices[totalIndices];

    // Read the indices
    for (uint32_t i = 0; i < totalIndices; i++) {
        ifs >> indices[i];
        ifs.ignore();
    }

    // Read the total number of control points
    uint32_t totalControlPoints;
    ifs >> totalControlPoints;

    // Read the control points
    Vec3f controlPoints[totalControlPoints];
    for (uint32_t i = 0; i < totalControlPoints; i++) {
        ifs >> controlPoints[i];
    }


    // Precalculate the M * P * M^T for each patch
    for (int i = 0; i < totalPatches; ++i) {
        vector<float> xValues;
        vector<float> yValues;
        vector<float> zValues;

        for (int j = 0; j < PATCH_SIZE; ++j) {
            Vec3f point = controlPoints[indices[i*PATCH_SIZE + j]];
            xValues.push_back(point.GetX());
            yValues.push_back(point.GetY());
            zValues.push_back(point.GetZ());
        }

        Mat xMatrix(4, 4, xValues);
        Mat yMatrix(4, 4, yValues);
        Mat zMatrix(4, 4, zValues);

        res->mPatches.push_back({xMatrix, yMatrix, zMatrix});
    }

    res->mTesselation = tesselation;

    ifs.close();

#ifndef NDEBUG
    cout << "BezierPatch created successfully." << endl;
    cout << "Total indices: " << totalIndices << endl;
    cout << "Total control points: " << totalControlPoints << endl;
    cout << "Tesselation: " << res->mTesselation << endl;
    for (int i = 0; i < totalIndices; ++i) {
        cout << "Patch " << i << ": " << indices[i] << endl;
    }
    cout << "Control points: " << endl;
    for (int i = 0; i < totalControlPoints; ++i) {
        cout << controlPoints[i] << endl;
    }
#endif

    return res;
}

void BezierPatch::BezierPoint(uint32_t p, float u, float v) {
    // p(u,v) = [u^3 u^2 u 1] * M * P * M^T * [v^3 v^2 v 1]^T

    Mat bu(1, 4, {u*u*u, u*u, u, 1});
    Mat bv(4, 1, {v*v*v, v*v, v, 1});
    vector<Mat> patch = mPatches.at(p);

    // Point
    Mat mx = bu * BezierMatrix * patch.at(0) * BezierMatrix * bv;
    Mat my = bu * BezierMatrix * patch.at(1) * BezierMatrix * bv;
    Mat mz = bu * BezierMatrix * patch.at(2) * BezierMatrix * bv;

    mVertices.emplace_back(mx.Get(0), my.Get(0), mz.Get(0));

    // Normal
    Mat mdv(4, 1, {3*v*v, 2*v, 1, 0});
    Mat mdu(1, 4, {3*u*u, 2*u, 1, 0});

    Mat mxu = mdu * BezierMatrix * patch.at(0) * BezierMatrix * bv;
    Mat myu = mdu * BezierMatrix * patch.at(1) * BezierMatrix * bv;
    Mat mzu = mdu * BezierMatrix * patch.at(2) * BezierMatrix * bv;

    Mat mxv = bu * BezierMatrix * patch.at(0) * BezierMatrix * mdv;
    Mat myv = bu * BezierMatrix * patch.at(1) * BezierMatrix * mdv;
    Mat mzv = bu * BezierMatrix * patch.at(2) * BezierMatrix * mdv;

    Vec3f normalU = Vec3f(mxu.Get(0), myu.Get(0), mzu.Get(0));
    Vec3f normalV = Vec3f(mxv.Get(0), myv.Get(0), mzv.Get(0));

    Vec3f normal = Vec3f::Cross(normalU, normalV);

    mNormals.emplace_back(Vec3f::Normalize(normal));
}

void BezierPatch::Tessellate(const char *pathToFile) {

    uint32_t patchSize = mPatches.size();

    for (int p = 0; p < patchSize; ++p) {
        for (int tv = 0; tv < mTesselation; ++tv) {
            float v = static_cast<float>(tv)/static_cast<float>(mTesselation);

            for (int tu = 0; tu < mTesselation; ++tu) {
                float u = static_cast<float>(tu)/static_cast<float>(mTesselation);

                float delta = 1.0f/static_cast<float>(mTesselation);

                BezierPoint(p, u, v);
                BezierPoint(p, u, (v + delta));
                BezierPoint(p, (u + delta), (v + delta));

                BezierPoint(p, u, v);
                BezierPoint(p, (u + delta), (v + delta));
                BezierPoint(p, (u + delta), v);

                mTextureCoordinates.emplace_back(u + delta, v - delta,0);
                mTextureCoordinates.emplace_back(u, v - delta,0);
                mTextureCoordinates.emplace_back(u, v,0);

                mTextureCoordinates.emplace_back(u, v,0);
                mTextureCoordinates.emplace_back(u + delta, v,0);
                mTextureCoordinates.emplace_back(u + delta, v - delta,0);

            }
        }
    }

    DumpModel(pathToFile, mVertices, mNormals, mTextureCoordinates);
}
