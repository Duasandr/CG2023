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


namespace cg_engine {
    using cg_math::Vec3f;

    TranslateCurve::TranslateCurve(float time, bool align) : mTime(time) , mAlign(align) { }

    void getGlobalCatmullRomPoint(float gt, float *pos, float *deriv) {

        float t = gt * POINT_COUNT; // this is the real global t
        int index = floor(t);  // which segment
        t = t - index; // where within  the segment

        // indices store the points
        int indices[4];
        indices[0] = (index + POINT_COUNT-1)%POINT_COUNT;
        indices[1] = (indices[0]+1)%POINT_COUNT;
        indices[2] = (indices[1]+1)%POINT_COUNT;
        indices[3] = (indices[2]+1)%POINT_COUNT;

        getCatmullRomPoint(t, p[indices[0]], p[indices[1]], p[indices[2]], p[indices[3]], pos, deriv);
    }

    void TranslateCurve::Apply() {
        float time = glutGet(GLUT_ELAPSED_TIME) / 1000.0f;
        float angle = fmodf(time, mTime) / mTime * 360.0f;

        // pos = g(t)
        float pos[3];
        // deriv = g'(t)
        float deriv[3];

        getGlobalCatmullRomPoint(t, pos, deriv);

        // translate to new position
        glTranslatef(pos[0], pos[1], pos[2]);

        // rotate to face the direction of the curve (deriv)
        float x[3] = {deriv[0], deriv[1], deriv[2]};
        normalize(x);

        float z[3];
        cross(x, prev_y, z);
        normalize(z);

        float y[3];
        cross(z,x,y);
        normalize(y);

        for (int i = 0; i < 3; ++i) {
            prev_y[i] = y[i];
        }

        // build the rotation matrix 4x4
        float m[16];

        buildRotMatrix(x,y,z,m);

        // apply rotation
        glMultMatrixf(m);


    }

    void multMatrixVector(float m[4][4], float *v, float *res) {

        for (int j = 0; j < 4; ++j) {
            res[j] = 0;
            for (int k = 0; k < 4; ++k) {
                res[j] += v[k] * m[j][k];
            }
        }

    }

    void TranslateCurve::getCatmullRomPoint(float t, float *p0, float *p1, float *p2, float *p3, float *pos, float *deriv) {

        // catmull-rom matrix
        float m[4][4] = {	{-0.5f,  1.5f, -1.5f,  0.5f},
                             { 1.0f, -2.5f,  2.0f, -0.5f},
                             {-0.5f,  0.0f,  0.5f,  0.0f},
                             { 0.0f,  1.0f,  0.0f,  0.0f}};


        for(int i = 0; i < 3; i++) {
            // p0, p1, p2, p3 are the control points
            float p[4] = {p0[i], p1[i], p2[i], p3[i]};
            float a[4];

            // Compute A = M * P
            multMatrixVector(m, p, a);

            // Compute pos = T * A
            pos[i] =  t * t * t * a[0] + t * t * a[1] + t * a[2] + a[3];

            // compute deriv = T' * A
            deriv[i] = 3 * t * t * a[0] + 2 * t * a[1] + a[2];
        }
    }

    void TranslateCurve::getGlobalCatmullRomPoint(float gt, float *pos, float *deriv) {
        int pointCount = mPoints.size();
        float t = gt * pointCount; // this is the real global t
        int index = floor(t);  // which segment
        t = t - index; // where within  the segment

        // indices store the points
        int indices[4];
        indices[0] = (index + pointCount-1)%pointCount;
        indices[1] = (indices[0]+1)%pointCount;
        indices[2] = (indices[1]+1)%pointCount;
        indices[3] = (indices[2]+1)%pointCount;

        getCatmullRomPoint(t, p[indices[0]], p[indices[1]], p[indices[2]], p[indices[3]], pos, deriv);
    }
} // cg_engine