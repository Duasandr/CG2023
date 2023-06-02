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

    const Mat C_MAT(4, 4, {1.0f, 1.0f, -1.0f, 1.0f,
                                    0.0f, 0.0f, 0.0f, 1.0f,
                                    1.0f, 1.0f, 1.0f, 1.0f,
                                    6.0f, 4.0f, 2.0f, 1.0f});

    TranslateCurve::TranslateCurve(float time, bool align) : mTime(time) , mAlign(align) {
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

        Vec3f p0 = mPoints[mCurrentIndices[0]];
        Vec3f p1 = mPoints[mCurrentIndices[1]];
        Vec3f p2 = mPoints[mCurrentIndices[2]];
        Vec3f p3 = mPoints[mCurrentIndices[3]];

        Mat mpx(1,4, {p0.GetX(), p1.GetX(), p2.GetX(), p3.GetX()});
        Mat mpy(1,4, {p0.GetY(), p1.GetY(), p2.GetY(), p3.GetY()});
        Mat mpz(1,4, {p0.GetZ(), p1.GetZ(), p2.GetZ(), p3.GetZ()});

        Mat resX = mpx * CATMULL_ROM_MAT;
        Mat resY = mpy * CATMULL_ROM_MAT;
        Mat resZ = mpz * CATMULL_ROM_MAT;

        float x = powf(t,3.0) * resX.Get(0) + powf(t,2.0) * resX.Get(1) + t * resX.Get(2) + resX.Get(3);
        float y = powf(t,3.0) * resY.Get(0) + powf(t,2.0) * resY.Get(1) + t * resY.Get(2) + resY.Get(3);
        float z = powf(t,3.0) * resZ.Get(0) + powf(t,2.0) * resZ.Get(1) + t * resZ.Get(2) + resZ.Get(3);

        return {x,y,z};
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
        Vec3f p0 = mPoints[mCurrentIndices[0]];
        Vec3f p1 = mPoints[mCurrentIndices[1]];
        Vec3f p2 = mPoints[mCurrentIndices[2]];
        Vec3f p3 = mPoints[mCurrentIndices[3]];

        Mat mpx(1,4, {p0.GetX(), p1.GetX(), p2.GetX(), p3.GetX()});
        Mat mpy(1,4, {p0.GetY(), p1.GetY(), p2.GetY(), p3.GetY()});
        Mat mpz(1,4, {p0.GetZ(), p1.GetZ(), p2.GetZ(), p3.GetZ()});

        Mat resX = mpx * CATMULL_ROM_MAT;
        Mat resY = mpy * CATMULL_ROM_MAT;
        Mat resZ = mpz * CATMULL_ROM_MAT;

        float x = 3 * powf(t, 2.0) * resX.Get(0) + 2 * t * resX.Get(1) + resX.Get(2);
        float y = 3 * powf(t, 2.0) * resY.Get(0) + 2 * t * resY.Get(1) + resY.Get(2);
        float z = 3 * powf(t, 2.0) * resZ.Get(0) + 2 * t * resZ.Get(1) + resZ.Get(2);

        return {x,y,z};
    }

    void TranslateCurve::Align(float t) {
        Vec3f up = Vec3f(0,1,0);
        Vec3f d = GetCatmullRomDerivative(t);
        Vec3f x = Vec3f::Normalize(d);
        Vec3f z = Vec3f::Normalize(Vec3f::Cross(x, up));
        Vec3f y = Vec3f::Normalize(Vec3f::Cross(z, x));

        Mat rot = Mat::RotationMatrix(x, y, z);

        glMultMatrixf(rot.GetData());
    }
} // cg_engine