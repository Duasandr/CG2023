//
// Created by Sandro Duarte on 03/04/2023.
//

#ifndef ENGINE_FIRST_PERSON_H
#define ENGINE_FIRST_PERSON_H

#include "world/camera/CameraType.h"

namespace cg_engine {

    class FirstPerson : public CameraType {
    public:
        FirstPerson();

        void Move(Camera &camera, unsigned char option) override;
        void MoveLeft(Camera &camera) override;
        void MoveRight(Camera &camera) override;
        void MoveUp(Camera &camera) override;
        void MoveDown(Camera &camera) override;
        void MoveForward(Camera &camera) override;
        void MoveBackward(Camera &camera) override;

        int GetType() override;

    private:
        void UpdateCameraVectors(Camera &camera);

        cg_math::Vec3f mCameraFront;
        cg_math::Vec3f mCameraRight;
        float mCameraSpeed;
    };

} // cg_engine

#endif //ENGINE_FIRST_PERSON_H
