//
// Created by Sandro Duarte on 10/03/2023.
//
#include "Camera.h"

namespace cg_engine {
    using cg_math::Vec3f;

    Camera::Camera() {
        mPosition = Vec3f();
        mLookAt = Vec3f();
        mUp = Vec3f();
        mProjection = Vec3f();
        mAlpha = 0.0f;
        mBeta = 0.0f;
        mRadius = 0.0f;
    }

    Camera::~Camera() {

    }

    void Camera::SetPosition(float x, float y, float z) {
        mPosition = Vec3f(x, y, z);

        mRadius = sqrt(x * x + y * y + z * z);
        mAlpha = acos(y / mRadius);
        mBeta = atan2(y, x);
    }

    void Camera::SetLookAt(float x, float y, float z) {
        mLookAt = Vec3f(x, y, z);
    }

    void Camera::SetUp(float x, float y, float z) {
        mUp = Vec3f(x, y, z);
    }

    void Camera::SetProjection(float fov, float near, float far) {
        mProjection = Vec3f(fov, near, far);
    }

    Vec3f Camera::GetPosition() const {
        return mPosition;
    }

    cg_math::Vec3f Camera::GetLookAt() const {
        return mLookAt;
    }

    cg_math::Vec3f Camera::GetUp() const {
        return mUp;
    }

    cg_math::Vec3f Camera::GetProjection() const {
        return mProjection;
    }

    void Camera::FreeMoveLeft() {
        mAlpha -= 0.1;

        mPosition.SphereToCartesian(mAlpha, mBeta, mRadius);
    }

    void Camera::FreeMoveRight() {
        mAlpha += 0.1;

        mPosition.SphereToCartesian(mAlpha, mBeta, mRadius);
    }

    void Camera::FreeMoveUp() {
        mBeta += 0.1;

        if(mBeta > M_PI_2) {
            mBeta = M_PI_2;
        }


        mPosition.SphereToCartesian(mAlpha, mBeta, mRadius);
    }

    void Camera::FreeMoveDown() {
        mBeta -= 0.1;

        if(mBeta < -M_PI_2) {
            mBeta = -M_PI_2;
        }


        mPosition.SphereToCartesian(mAlpha, mBeta, mRadius);
    }

    void Camera::FreeMoveBack() {
        mRadius += 0.1;

        mPosition.SphereToCartesian(mAlpha, mBeta, mRadius);
    }

    void Camera::FreeMoveFront() {
        mRadius -= 0.1;

        mPosition.SphereToCartesian(mAlpha, mBeta, mRadius);
    }
} // cg_engine