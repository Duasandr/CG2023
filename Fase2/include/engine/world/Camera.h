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
        // Default constructor
        Camera();
        // Default destructor
        virtual ~Camera();

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
         * @brief Moves the camera left in a spherical way.
        */
        void FreeMoveLeft();

        /**
         * @brief Moves the camera right in a spherical way.
        */
        void FreeMoveRight();

        /**
         * @brief Moves the camera up in a spherical way.
        */
        void FreeMoveUp();

        /**
         * @brief Moves the camera down in a spherical way.
        */
        void FreeMoveDown();

        /**
         * @brief Moves the camera front in a spherical way.
        */
        void FreeMoveFront();

        /**
         * @brief Moves the camera back in a spherical way.
        */
        void FreeMoveBack();

        void LookLeft();
        void LookRight();
        void LookFront();
        void LookBack();

        /**
         * @brief Gets the position of the camera.
         * @return The position of the camera.
         */
        cg_math::Vec3f GetPosition() const;

        /**
         * @brief Gets the lookAt point of the camera.
         * @return The lookAt point of the camera.
         */
        cg_math::Vec3f GetLookAt() const;

        /**
         * @brief Gets the up vector of the camera.
         * @return The up vector of the camera.
         */
        cg_math::Vec3f GetUp() const;

        /**
         * @brief Gets the projection vector of the camera.
         * @return The projection vector of the camera.
         */
        cg_math::Vec3f GetProjection() const;

    private:
        // The position of the camera
        cg_math::Vec3f mPosition;
        // The lookAt point of the camera
        cg_math::Vec3f mLookAt;
        // The up vector of the camera
        cg_math::Vec3f mUp;
        // The projection vector of the camera
        cg_math::Vec3f mProjection;

        // The radius of the camera
        float mAlpha;
        // The angle between the camera and the origin
        float mBeta;
        // The distance between the camera and the origin
        float mRadius;
    };

} // cg_engine

#endif //ENGINE_CAMERA_H
