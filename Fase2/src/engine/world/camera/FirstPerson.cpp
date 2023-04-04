//
// Created by Sandro Duarte on 03/04/2023.
//

#include "world/camera/FirstPerson.h"

namespace cg_engine {

    FirstPerson::FirstPerson() {
        mCameraFront = cg_math::Vec3f(0.0f, 0.0f, -1.0f);
        mCameraSpeed = 50.0f;
    }

    void FirstPerson::Move(Camera &camera, const unsigned char option) {
        CameraType::Move(camera, option);
        UpdateCameraVectors(camera);
    }

    void FirstPerson::MoveLeft(Camera &camera) {
        camera.GetPosition() -= mCameraRight * mCameraSpeed;
    }

    void FirstPerson::MoveRight(Camera &camera) {
        camera.GetPosition() += mCameraRight * mCameraSpeed;
    }

    void FirstPerson::MoveUp(Camera &camera) {
    }

    void FirstPerson::MoveDown(Camera &camera) {
    }

    void FirstPerson::MoveForward(Camera &camera) {
        camera.GetPosition() +=  mCameraFront * mCameraSpeed;
    }

    void FirstPerson::MoveBackward(Camera &camera) {
        camera.GetPosition() -=  mCameraFront * mCameraSpeed;
    }

    int FirstPerson::GetType() {
        return CameraType::FIRST_PERSON;
    }

    void FirstPerson::UpdateCameraVectors(Camera &camera) {
            // calculate the new Front vector
            mCameraFront.Normalize();
            // also re-calculate the Right and Up vector
            mCameraRight = mCameraFront.Cross(camera.GetUp());  // normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
            mCameraRight.Normalize();
            camera.GetUp()  = mCameraRight.Cross(mCameraFront);
            camera.GetLookAt() = camera.GetPosition() + mCameraFront;

    }

} // cg_engine