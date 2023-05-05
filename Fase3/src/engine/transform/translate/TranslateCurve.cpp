//
// Created by Sandro Duarte on 19/03/2023.
//
#ifdef __APPLE__
#include <glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif
#include "translate/TranslateCurve.h"
#include "Mat.h"


namespace cg_engine {
    using cg_math::Vec3f;
    using cg_math::Mat;

    // catmull-rom matrix
    const Mat CATMULL_ROM_MAT(4, 4 , {-0.5f, 1.5f, -1.5f, 0.5f,
                                      1.0f, -2.5f, 2.0f, -0.5f,
                                      -0.5f, 0.0f, 0.5f, 0.0f,
                                      0.0f, 1.0f, 0.0f, 0.0f});

    const Mat C_MAT(4, 4, {1, 1, -1, 1,
                           0, 0, 0, 1,
                           1, 1, 1, 1,
                           6, 4, 2, 1});

    TranslateCurve::TranslateCurve(float time, bool align) : mTime(time) , mAlign(align) {
        mPrevY = Vec3f(0,-1,0);
    }


    void TranslateCurve::AddPoint(const cg_math::Vec3f &point) { mPoints.push_back(point); }



    void TranslateCurve::Apply() {

        float delta = glutGet(GLUT_ELAPSED_TIME) / 1000.0f;

        // Compute the speed at which the object should move
        float speed = 1 / mTime; // mTime seconds to complete the curve

        // Compute the total distance traveled by the object
        float distance = speed * delta;

        Vec3f p = GetCatmullRomPoint(distance);

#ifndef NDEBUG
        glBegin(GL_LINE_LOOP);
        glColor3f(1, 1, 1);
        float gt = 0;
        while (gt < 1) {
            Vec3f ps = GetCatmullRomPoint(gt);
            glVertex3f(ps.GetX(),ps.GetY(),ps.GetZ());
            gt += 1.0/1000;
        }
        glEnd();
#endif

        glTranslatef(p.GetX(), p.GetY(), p.GetZ());

        if(mAlign) {
            Align(distance);
        }
    }

    cg_math::Vec3f TranslateCurve::GetCatmullRomPoint(float gt) {
        float t = ComputeIndices(gt);

        Mat mt(1,4, {t*t*t, t*t, t, 1});

        Mat mp(4,4,{mPoints[mCurrentIndices[0]].GetX(), mPoints[mCurrentIndices[0]].GetY(), mPoints[mCurrentIndices[0]].GetZ(), 1,
                    mPoints[mCurrentIndices[1]].GetX(), mPoints[mCurrentIndices[1]].GetY(), mPoints[mCurrentIndices[1]].GetZ(), 1,
                    mPoints[mCurrentIndices[2]].GetX(), mPoints[mCurrentIndices[2]].GetY(), mPoints[mCurrentIndices[2]].GetZ(), 1,
                    mPoints[mCurrentIndices[3]].GetX(), mPoints[mCurrentIndices[3]].GetY(), mPoints[mCurrentIndices[3]].GetZ(), 1});

        Mat mpc = mp * C_MAT;
        Mat res = mt * CATMULL_ROM_MAT * mpc;

        return {res.Get(0,0), res.Get(0,1), res.Get(0,2)};
    }

    float TranslateCurve::ComputeIndices(float gt) {
        int POINT_COUNT = mPoints.size();
        float t = gt * mPoints.size(); // this is the real global t
        int index = floor(t);  // which segment
        t = t - index; // where within  the segment

        // indices store the points

        mCurrentIndices[0] = (index + POINT_COUNT-1)%POINT_COUNT;
        mCurrentIndices[1] = (mCurrentIndices[0]+1)%POINT_COUNT;
        mCurrentIndices[2] = (mCurrentIndices[1]+1)%POINT_COUNT;
        mCurrentIndices[3] = (mCurrentIndices[2]+1)%POINT_COUNT;
        return t;
    }

    cg_math::Vec3f TranslateCurve::GetCatmullRomDerivative(float t) {

        Mat mt(1,4, {3*t*t, 2*t, 1, 0});

        Mat mp(4,4,{mPoints[mCurrentIndices[0]].GetX(), mPoints[mCurrentIndices[0]].GetY(), mPoints[mCurrentIndices[0]].GetZ(), 1,
                    mPoints[mCurrentIndices[1]].GetX(), mPoints[mCurrentIndices[1]].GetY(), mPoints[mCurrentIndices[1]].GetZ(), 1,
                    mPoints[mCurrentIndices[2]].GetX(), mPoints[mCurrentIndices[2]].GetY(), mPoints[mCurrentIndices[2]].GetZ(), 1,
                    mPoints[mCurrentIndices[3]].GetX(), mPoints[mCurrentIndices[3]].GetY(), mPoints[mCurrentIndices[3]].GetZ(), 1});

        Mat mpc = mp * C_MAT;
        Mat res = mt * CATMULL_ROM_MAT * mpc;

        return {res.Get(0,0), res.Get(0,0), res.Get(0,0)};
    }

    void TranslateCurve::Align(float t) {
        Vec3f d = GetCatmullRomDerivative(t);
        Vec3f x = Vec3f::Normalize(d);
        Vec3f z = Vec3f::Normalize(Vec3f::Cross(x, mPrevY));
        Vec3f y = Vec3f::Normalize(Vec3f::Cross(z, x));
        mPrevY = y;

        Mat rot = Mat::RotationMatrix(x, y, z);

        glMultMatrixf(rot.GetData());
    }
} // cg_engine