//
// Created by Sandro Duarte on 24/04/2023.
//

#include <fstream>
#include "primitives/BezierPatch.h"
#include "Mat.h"
#include "utils/DumpVertices.h"

using std::ifstream;
using std::cerr;
using std::cout;
using std::endl;
using cg_math::Vec3f;
using cg_math::Mat;
using std::vector;

/**
 * ////////////////////////////////
 * // Constructor and destructor
 * ////////////////////////////////
 */

BezierPatch::BezierPatch() {
    mTesselation = 0;
    mTotalIndices = 0;
    mTotalControlPoints = 0;
    mIndices = nullptr;
    mControlPoints = nullptr;
}

BezierPatch::~BezierPatch() {
    delete[] mIndices;
    delete[] mControlPoints;
}

/**
 * ////////////////////////////////
 * // Static methods
 * ////////////////////////////////
 */

BezierPatch *BezierPatch::Create(const char *pathToFile, uint32_t tesselation) {
    BezierPatch *res = new BezierPatch();

    ifstream ifs(pathToFile);

    // Check if file exists
    if (!ifs.is_open()) {
        cerr << "File " << pathToFile << " not found." << endl;
        return nullptr;
    }

    // Read the total number of rows of the patch array (patch array is a 2D array of indices)
    // The total number of columns is fixed to 16
    // Each patch has 16 points
    uint32_t rows;
    ifs >> rows;

    // Allocate memory for the indices
    res->mTotalIndices = rows * PATCH_SIZE;
    res->mIndices = new uint32_t[res->mTotalIndices];

    // Read the indices
    for (uint32_t i = 0; i < res->mTotalIndices; i++) {
        ifs >> res->mIndices[i];
        ifs.ignore();
    }

    // Read the total number of control points
    ifs >> res->mTotalControlPoints;

    // Allocate memory for the control points
    res->mControlPoints = new Vec3f[res->mTotalControlPoints];

    // Read the control points
    for (uint32_t i = 0; i < res->mTotalControlPoints; i++) {
        ifs >> res->mControlPoints[i];
    }

    res->mTesselation = tesselation;

    ifs.close();

#ifndef NDEBUG
    cout << "BezierPatch created successfully." << endl;
    cout << "Total indices: " << res->mTotalIndices << endl;
    cout << "Total control points: " << res->mTotalControlPoints << endl;
    cout << "Tesselation: " << res->mTesselation << endl;
    for (int i = 0; i < rows; ++i) {
        cout << "Patch " << i << ": ";
        for (int j = 0; j < PATCH_SIZE; ++j) {
            cout << res->mIndices[i * PATCH_SIZE + j] << " ";
        }
        cout << endl;
    }
    cout << "Control points: " << endl;
    for (int i = 0; i < res->mTotalControlPoints; ++i) {
        cout << res->mControlPoints[i] << endl;
    }
#endif

    return res;
}

Vec3f BezierPatch::BezierPoint(uint32_t p, float u, float v) {
    // p(u,v) = [u^3 u^2 u 1] * M * P * M^T * [v^3 v^2 v 1]^T

    Mat bu = {u*u*u, u*u, u, 1};
    Mat bv = {v*v*v, v*v, v, 1};

    Mat m = {
                        {-1,  3, -3,  1},
                        {3, -6,  3,  0},
                        {-3,  3,  0,  0},
                        {1,  0,  0,  0}
    };

    Mat px = {
            {
                mControlPoints[mIndices[p]].GetX(),
                mControlPoints[mIndices[p+1]].GetX(),
                mControlPoints[mIndices[p+2]].GetX(),
                mControlPoints[mIndices[p+3]].GetX()
            },
            {
                mControlPoints[mIndices[p+4]].GetX(),
                mControlPoints[mIndices[p+5]].GetX(),
                mControlPoints[mIndices[p+6]].GetX(),
                mControlPoints[mIndices[p+7]].GetX()
            },
            {
                mControlPoints[mIndices[p + 8]].GetX(),
                mControlPoints[mIndices[p + 9]].GetX(),
                mControlPoints[mIndices[p + 10]].GetX(),
                mControlPoints[mIndices[p + 11]].GetX()
            },
            {
                mControlPoints[mIndices[p + 12]].GetX(),
                mControlPoints[mIndices[p + 13]].GetX(),
                mControlPoints[mIndices[p + 14]].GetX(),
                mControlPoints[mIndices[p + 15]].GetX()
            }
    };

    Mat py = {
            {
                    mControlPoints[mIndices[p]].GetY(),
                    mControlPoints[mIndices[p+1]].GetY(),
                    mControlPoints[mIndices[p+2]].GetY(),
                    mControlPoints[mIndices[p+3]].GetY()
            },
            {
                    mControlPoints[mIndices[p+4]].GetY(),
                    mControlPoints[mIndices[p+5]].GetY(),
                    mControlPoints[mIndices[p+6]].GetY(),
                    mControlPoints[mIndices[p+7]].GetY()
            },
            {
                    mControlPoints[mIndices[p + 8]].GetY(),
                    mControlPoints[mIndices[p + 9]].GetY(),
                    mControlPoints[mIndices[p + 10]].GetY(),
                    mControlPoints[mIndices[p + 11]].GetY()
            },
            {
                    mControlPoints[mIndices[p + 12]].GetY(),
                    mControlPoints[mIndices[p + 13]].GetY(),
                    mControlPoints[mIndices[p + 14]].GetY(),
                    mControlPoints[mIndices[p + 15]].GetY()
            }
    };

    Mat pz = {
            {
                    mControlPoints[mIndices[p]].GetZ(),
                    mControlPoints[mIndices[p+1]].GetZ(),
                    mControlPoints[mIndices[p+2]].GetZ(),
                    mControlPoints[mIndices[p+3]].GetZ()
            },
            {
                    mControlPoints[mIndices[p+4]].GetZ(),
                    mControlPoints[mIndices[p+5]].GetZ(),
                    mControlPoints[mIndices[p+6]].GetZ(),
                    mControlPoints[mIndices[p+7]].GetZ()
            },
            {
                    mControlPoints[mIndices[p + 8]].GetZ(),
                    mControlPoints[mIndices[p + 9]].GetZ(),
                    mControlPoints[mIndices[p + 10]].GetZ(),
                    mControlPoints[mIndices[p + 11]].GetZ()
            },
            {
                    mControlPoints[mIndices[p + 12]].GetZ(),
                    mControlPoints[mIndices[p + 13]].GetZ(),
                    mControlPoints[mIndices[p + 14]].GetZ(),
                    mControlPoints[mIndices[p + 15]].GetZ()
            }
    };


    Mat mtx = bu * m * px * Mat::Transpose(m);
    Mat mty = bu * m * py * Mat::Transpose(m);
    Mat mtz = bu * m * pz * Mat::Transpose(m);

    Mat x = bv * mtx;
    Mat y = bv * mty;
    Mat z = bv * mtz;

    return {x.Get(0,0), y.Get(0,0), z.Get(0,0)};
}

void BezierPatch::Tessellate(const char *pathToFile) {
    vector<Vec3f> vertices;

    // for each patch
    for (int p = 0; p < mTotalIndices; ++p) {
        // for each tv (tessellation value)
        for (int tv = 0; tv < mTesselation; ++tv) {
            float v = static_cast<float>(tv)/static_cast<float>(mTesselation);

            // for each tu (tesselation unit)
            for (int tu = 0; tu < mTesselation; ++tu) {
                float u = static_cast<float>(tu)/static_cast<float>(mTesselation);

                // add the 6 vertices of the triangle
                // the order is important because the vertices are added in cc order
                // this is done to avoid having to calculate the normals

                vertices.push_back(BezierPoint(p, (u + (1.0f/static_cast<float>(mTesselation))), (v + (1.0f/static_cast<float>(mTesselation)))));
                vertices.push_back(BezierPoint(p, u, (v + (1.0f/static_cast<float>(mTesselation)))));
                vertices.push_back(BezierPoint(p, u, v));

                vertices.push_back(BezierPoint(p, u, v));
                vertices.push_back(BezierPoint(p, (u + (1.0f/static_cast<float>(mTesselation))), v));
                vertices.push_back(BezierPoint(p, (u + (1.0f/static_cast<float>(mTesselation))), (v + (1.0f/static_cast<float>(mTesselation)))));
            }
        }
    }
    DumpVertices(pathToFile, vertices.size(), vertices);
}
