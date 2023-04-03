//
// Created by Sandro Duarte on 03/04/2023.
//

#ifndef ENGINE_SPHERICAL_CONTROLLER_H
#define ENGINE_SPHERICAL_CONTROLLER_H
#include "CameraType.h"
#include "Camera.h"

namespace cg_engine {

    class Spherical : public CameraType {
    public:
        Spherical();
        explicit Spherical(const cg_engine::Camera &camera);

        void Move(cg_engine::Camera &camera, unsigned char option) override;
        void MoveLeft(cg_engine::Camera &camera) override;
        void MoveRight(cg_engine::Camera &camera) override;
        void MoveUp(cg_engine::Camera &camera) override;
        void MoveDown(cg_engine::Camera &camera) override;
        void MoveForward(cg_engine::Camera &camera) override;
        void MoveBackward(cg_engine::Camera &camera) override;

        int GetType() override;

    private:
        /**
         * @brief The alpha angle
         * @details The alpha angle is the angle between the x-axis and the projection of the position vector on the xz plane.
         */
        float mAlpha;
        /**
         * @brief The beta angle
         * @details The beta angle is the angle between the z-axis and the projection of the position vector on the xz plane.
         */
        float mBeta;
        /**
         * @brief The radius
         * @details The radius is the distance between the camera and the origin.
         */
        float mRadius;
    };

} // cg_camera

#endif //ENGINE_SPHERICAL_CONTROLLER_H
