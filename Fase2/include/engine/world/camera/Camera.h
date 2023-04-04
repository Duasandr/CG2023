//
// Created by Sandro Duarte on 10/03/2023.
//

#ifndef ENGINE_CAMERA_H
#define ENGINE_CAMERA_H
#include "Vec3f.h"
#include "tinyxml2.h"

/**
 * @brief The cg_engine namespace.
 * @details It contains all the classes and functions of the engine.
 */
namespace cg_engine {
    class CameraType;

    /**
     * @brief Camera class.
     * @details It represents the camera of the scene.
     * It has a position, a lookAt point and an up vector.
     * It also has a projection vector, which contains the field of view, the near and far planes.
     * It also has a radius, which is the distance between the camera and the origin.
     * It also has two angles, alpha and beta, which are the angles between the camera and the origin.
     * The camera can be moved freely or it can be moved in a spherical way.
     */
    class Camera {
    public:
        /**
         * @brief Default constructor.
         * @details It initializes the position, the lookAt point, the up vector and the projection vector.
         * It also initializes the radius, the alpha and the beta angles.
         */
        Camera();
        /**
         * @brief Default destructor.
         */
        virtual ~Camera() = default;

        /**
         * @brief Creates a camera from a XML block.
         * @param tag The XML block.
         * @return A pointer to the created camera.
         */
        static Camera* Create(tinyxml2::XMLElement *tag);

        /**
         * @brief Sets the position of the camera.
         * @param x The x coordinate of the position.
         * @param y The y coordinate of the position.
         * @param z The z coordinate of the position.
         */
        void SetPosition(float x, float y, float z);

        /**
         * @brief Sets the lookAt point of the camera.
         * @param x The x coordinate of the lookAt point.
         * @param y The y coordinate of the lookAt point.
         * @param z The z coordinate of the lookAt point.
         */
        void SetLookAt(float x, float y, float z);

        /**
         * @brief Sets the up vector of the camera.
         * @param x The x coordinate of the up vector.
         * @param y The y coordinate of the up vector.
         * @param z The z coordinate of the up vector.
         */
        void SetUp(float x, float y, float z);

        /**
         * @brief Sets the projection vector of the camera.
         * @param fov The field of view.
         * @param near The near plane.
         * @param far The far plane.
         */
        void SetProjection(float fov, float near, float far);

        /**
         * @brief Sets the type of the camera.
         * @param cameraType The type of the camera.
         */
        void SetCameraType(CameraType *cameraType);

        /**
         * @brief Gets the position of the camera.
         * @return The position of the camera.
         */
        cg_math::Vec3f &GetPosition();
        cg_math::Vec3f const &GetPosition() const;

        /**
         * @brief Gets the lookAt point of the camera.
         * @return The lookAt point of the camera.
         */
        cg_math::Vec3f &GetLookAt();

        /**
         * @brief Gets the up vector of the camera.
         * @return The up vector of the camera.
         */
        cg_math::Vec3f &GetUp();

        /**
         * @brief Gets the projection vector of the camera.
         * @return The projection vector of the camera.
         */
        cg_math::Vec3f &GetProjection();

        /**
         * @brief Moves the camera.
         * @details It moves the camera according to the option.
         * @param option
         */
        void Move(unsigned char option);

        void SwitchType();

    private:
        /**
         * @brief Type of the camera.
         * @details It can be free or spherical.
         */
        cg_engine::CameraType *mCameraType;

        /**
         * @brief mPosition of the camera.
         */
        cg_math::Vec3f mPosition;
        /**
         * @brief LookAt point of the camera.
         */
        cg_math::Vec3f mLookAt;
        /**
         * @brief mUp vector of the camera.
         */
        cg_math::Vec3f mUp;
        /**
         * @brief Projection vector of the camera.
         * @details It contains the field of view, the near and far planes.
         */
        cg_math::Vec3f mProjection;

    };

} // cg_engine

#endif //ENGINE_CAMERA_H
