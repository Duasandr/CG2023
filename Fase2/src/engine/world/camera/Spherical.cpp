//
// Created by Sandro Duarte on 03/04/2023.
//

#include "world/camera/Spherical.h"

namespace cg_engine {

    Spherical::Spherical() {
        mAlpha = 0;
        mBeta = 0;
        mRadius = 1;
    }

    Spherical::Spherical(const Camera &camera) {
        const float x = camera.GetPosition().GetX();
        const float y = camera.GetPosition().GetY();

        // The radius is the norm of the position vector.
        mRadius = camera.GetPosition().Norm();
        // The alpha angle is the angle between the x-axis and the projection of the position vector on the xz plane.
        mAlpha = acos(y / mRadius);
        // The beta angle is the angle between the z-axis and the projection of the position vector on the xz plane.
        mBeta = atan2(y, x);
    }

    void Spherical::Move(Camera &camera, const unsigned char option) {
        CameraType::Move(camera, option);
        camera.GetPosition().SphereToCartesian(mAlpha, mBeta, mRadius);
    }

    void Spherical::MoveLeft(Camera &camera) { mAlpha -= 0.1; }

    void Spherical::MoveRight(Camera &camera) { mAlpha += 0.1; }

    void Spherical::MoveUp(Camera &camera) { mBeta = mBeta + 0.1f > 1.5f ? 1.5f : mBeta + 0.1f; }

    void Spherical::MoveDown(Camera &camera) { mBeta = mBeta - 0.1f < -1.5f ? -1.5f : mBeta - 0.1f; }

    void Spherical::MoveForward(Camera &camera) { mRadius = mRadius + 1.0f < 1.5f ? 1.5f : mRadius - 1.0f; }

    void Spherical::MoveBackward(Camera &camera) { mRadius += 1.0f; }

    int Spherical::GetType() {
        return CameraType::SPHERICAL;
    }


} // cg_camera