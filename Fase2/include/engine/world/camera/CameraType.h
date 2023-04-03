//
// Created by Sandro Duarte on 03/04/2023.
//

#ifndef ENGINE_CAMERA_TYPE_H
#define ENGINE_CAMERA_TYPE_H
#include "Camera.h"

namespace cg_engine {

    /**
     * @brief CameraType class.
     * @details It represents the type of the camera.
     */
    class CameraType {
    public:
        enum type {
            FIRST_PERSON,
            SPHERICAL
        };

        virtual ~CameraType() = default;

        /**
         * @brief Moves the camera.
         * @details It moves the camera according to the option.
         * @param camera the camera to be moved
         * @param option the option to move the camera
         */
        virtual void Move(Camera &camera, unsigned char option);
        virtual void MoveLeft(Camera &camera) = 0;
        virtual void MoveRight(Camera &camera) = 0;
        virtual void MoveUp(Camera &camera) = 0;
        virtual void MoveDown(Camera &camera) = 0;
        virtual void MoveForward(Camera &camera) = 0;
        virtual void MoveBackward(Camera &camera) = 0;

        /**
         * @brief Gets the type of the camera.
         * @details It gets the type of the camera.
         * @return the type of the camera
         */
        virtual int GetType() = 0;

    };

} // cg_engine

#endif //ENGINE_CAMERA_TYPE_H
