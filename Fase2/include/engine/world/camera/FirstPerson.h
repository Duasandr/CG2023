//
// Created by Sandro Duarte on 03/04/2023.
//

#ifndef ENGINE_FIRST_PERSON_H
#define ENGINE_FIRST_PERSON_H

#include "world/camera/CameraType.h"

namespace cg_engine {

    //TODO: Add the ability to rotate the camera around.
    /**
     * @brief FirstPerson class.
     * @details It represents the first person camera. It can be moved freely.
     */
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

        /**
         * @brief The camera's front vector.
         * @details It is the vector that points to the front of the camera.
         * It is calculated from the camera's position and the lookAt point.
         */
        cg_math::Vec3f mFront;
        /**
         * @brief The camera's right vector.
         * @details It is the vector that points to the positive x axis of the camera.
         */
        cg_math::Vec3f mRight;
        /**
         * @brief The camera's speed.
         * @details It is the speed at which the camera moves.
         */
        float mSpeed;
    };

} // cg_engine

#endif //ENGINE_FIRST_PERSON_H
