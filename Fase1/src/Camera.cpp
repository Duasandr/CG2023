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
} // cg_engine