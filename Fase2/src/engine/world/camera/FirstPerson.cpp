//
// Created by Sandro Duarte on 03/04/2023.
//

#include "world/camera/FirstPerson.h"

namespace cg_engine {

    FirstPerson::FirstPerson() {
        mFront = cg_math::Vec3f(0.0f, 0.0f, -1.0f);
        mSpeed = 5.0f;
    }

    void FirstPerson::Move(Camera &camera, const unsigned char option) {
        CameraType::Move(camera, option);
        UpdateCameraVectors(camera);
    }

    void FirstPerson::MoveLeft(Camera &camera) {
        camera.GetPosition() -= mRight * mSpeed;
    }

    void FirstPerson::MoveRight(Camera &camera) {
        camera.GetPosition() += mRight * mSpeed;
    }

    void FirstPerson::MoveUp(Camera &camera) {

    }

    void FirstPerson::MoveDown(Camera &camera) {
    }

    void FirstPerson::MoveForward(Camera &camera) {
        camera.GetPosition() += mFront * mSpeed;
    }

    void FirstPerson::MoveBackward(Camera &camera) {
        camera.GetPosition() -= mFront * mSpeed;
    }

    int FirstPerson::GetType() {
        return CameraType::FIRST_PERSON;
    }

    void FirstPerson::UpdateCameraVectors(Camera &camera) {
            // calculate the new mFront vector
            mFront = cg_math::Vec3f::Normalize(mFront);
            // also re-calculate the mRight and mUp vector
            mRight = cg_math::Vec3f::Cross(mFront, camera.GetUp());  // normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
            mRight = cg_math::Vec3f::Normalize(mRight);
            camera.GetUp()  = cg_math::Vec3f::Cross(mRight, mFront);
            camera.GetLookAt() = camera.GetPosition() + mFront;

    }

} // cg_engine