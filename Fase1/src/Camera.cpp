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
    }

    Camera::~Camera() {

    }

    void Camera::SetPosition(float x, float y, float z) {
        mPosition = Vec3f(x, y, z);
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
} // cg_engine