//
// Created by Sandro Duarte on 10/03/2023.
//

#ifndef ENGINE_CAMERA_H
#define ENGINE_CAMERA_H
#include "Vec3f.h"
#include "utils/tinyxml2.h"

/**
 * @brief The cg_engine namespace.
 * @details It contains all the classes and functions of the engine.
 */
namespace cg_engine {

    /**
     * @brief Camera movement enum.
     * @details It represents the possible movements of the camera.
     */
    enum class CameraMovement {
        FORWARD,
        BACKWARD,
        LEFT,
        RIGHT
    };

    /**
     * @brief Camera class.
     * @details It represents the camera of the scene.
     */
    class Camera {
    public:
        /*
         * //////////////////////////////
         * // Constructors and destructor
         * //////////////////////////////
         */

        /**
         * @brief Default constructor.
         * @details It creates a camera with the default values.
         */
        Camera();
        /**
         * @brief Default destructor.
         */
        virtual ~Camera() = default;

        /*
         * //////////////////////////////
         * // Static methods
         * //////////////////////////////
         */

        /**
         * @brief Creates a camera from a XML block.
         * @param tag The XML block.
         * @return A pointer to the created camera.
         * @throws std::runtime_error when the camera block is invalid.
         */
        static Camera* Create(tinyxml2::XMLElement *tag);

        /*
         * //////////////////////////////
         * // Setters
         * //////////////////////////////
         */

        void SetPosition    (cg_math::Vec3f const &position);
        void SetLookAt      (cg_math::Vec3f const &lookAt);
        void SetUp          (cg_math::Vec3f const &up);
        void SetProjection  (cg_math::Vec3f const &projection);
        void SetDirection   (cg_math::Vec3f const &direction);
        void SetRadius      (float radius);

        /*
         * //////////////////////////////
         * // Getters
         * //////////////////////////////
         */

        cg_math::Vec3f GetPosition();
        cg_math::Vec3f GetLookAt();
        cg_math::Vec3f GetUp();
        cg_math::Vec3f GetProjection();

        /*
         * //////////////////////////////
         * // Instance methods
         * //////////////////////////////
         */

        /**
         * @brief Moves the camera.
         * @details It moves the camera in the direction of the movement in a rail like movement.
         * @param move The movement to be done.
         */
        void Move(CameraMovement move);
        /**
         * @brief Rotates the camera.
         * @details It rotates the camera taking into account the position of the mouse.
         * @param x The x mouse position.
         * @param y The y mouse position.
         */
        void Rotate(float x, float y);

    private:
        /*
         * //////////////////////////////
         * // Private methods
         * //////////////////////////////
         */

        /**
         * @brief Initializes the camera sphere coordinates.
         * @details It initializes the alpha, beta and radius of the camera.
         * @param x Initial camera x position.
         * @param y Initial camera y position.
         */
        void InitSphereCoords(float x, float y);

        /*
        * //////////////////////////////
        * // Private instance variables
        * //////////////////////////////
        */

        /**
         * @brief Point where the camera is located in the world.
         */
        cg_math::Vec3f mPosition;
        /**
         * @brief Vector that points to the front of the camera.
         */
        cg_math::Vec3f mDirection;
        /**
         * @brief Point where the camera is looking at.
         */
        cg_math::Vec3f mLookAt;
        /**
         * @brief Vector that points to the top of the camera.
         */
        cg_math::Vec3f mUp;
        /**
         * @brief Vector that points to the right of the camera. It is perpendicular to the direction and up vectors.
         */
        cg_math::Vec3f mRight;
        /**
         * @brief Vector that contains the projection information.
         * @details It contains the field of view, the near and far planes.
         */
        cg_math::Vec3f mProjection;
        /**
         * @brief Checks if the mouse is in the first position.
         */
        bool mFirstMouse;
        /**
         * @brief The last x mouse position.
         */
        float mLastX;
        /**
         * @brief The last y mouse position.
         */
        float mLastY;
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

} // cg_engine

#endif //ENGINE_CAMERA_H
