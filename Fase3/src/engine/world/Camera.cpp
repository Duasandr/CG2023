//
// Created by Sandro Duarte on 10/03/2023.
//
#ifdef __APPLE__
#include <glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif
#include "Camera.h"
#include "EngineParser.h"

//TODO: Camera still needs to be fixed. Rotation is not working properly.

namespace cg_engine {

    /**
     * @brief Number of tags of the camera block.
     */
#define CAMERA_TAG_NUM 4
    /**
     * @brief Position tag of the camera block in the array.
     */
#define CAMERA_TAG_POSITION 0
    /**
     * @brief Look at tag of the camera block in the array.
     */
#define CAMERA_TAG_LOOK_AT 1
    /**
     * @brief Up tag of the camera block in the array.
     */
#define CAMERA_TAG_UP 2
    /**
     * @brief Projection tag of the camera block in the array.
     */
#define CAMERA_TAG_PROJECTION 3
    /**
     * @brief Default camera sensitivity.
     */
#define CAMERA_SENSITIVITY 0.01f
    /**
      * @brief Default camera speed.
      */
#define CAMERA_SPEED 1.5f

    /*
     * //////////////////////////////
     * // Using declarations
     * //////////////////////////////
     */

    using tinyxml2::XMLElement;
    using cg_math::Vec3f;
    using cg_math::Mat;

    /*
    * //////////////////////////////
    * // Constructors and destructor
    * //////////////////////////////
    */

    Camera::Camera() {
        mPosition = Vec3f();
        mLookAt = Vec3f();
        mUp = Vec3f();
        mProjection = Vec3f();
        mFirstMouse = true;
        mLastX = 0;
        mLastY = 0;
        mAlpha = 0;
        mBeta = 0;
        mRadius = 0;
    }

    /*
    * //////////////////////////////
    * // Static methods
    * //////////////////////////////
    */

    Camera *Camera::Create(tinyxml2::XMLElement *block) {
        /**
         * Creates a new camera from an XML block.
         * It parses the position, the lookAt point, the up vector and the projection vector.
         * <camera>-----------------------------------------------------------------------------
         *   attribute "x"     "y"      "z"                                                     }
	     *  <position   x="100" y="100"  z="100" />            first child element "position"   }
	     *  <lookAt     x="0"   y="0"    z="0" />              first child element "lookAt"     }-> Block
	     *  <up         x="0"   y="1"    z="0" />              first child element "up"         }
         *   attribute "fov"      "near"   "far"                                                }
         *  <projection fov="100" near="1" far="1000" />       first child element "projection" }
	     * </camera>----------------------------------------------------------------------------}
         */
        auto *res = new Camera();

        // Parse the position of the camera from the XML block.
        XMLElement *tags[CAMERA_TAG_NUM] = {
                block->FirstChildElement("position"),
                block->FirstChildElement("lookAt"),
                block->FirstChildElement("up"),
                block->FirstChildElement("projection"),
        };

        // Check if the XML block is valid.
        for (auto &tag : tags) {
            if(tag == nullptr) {
                throw std::runtime_error("Camera::Create: Invalid XML block: " + std::string(block->Name()));
            }
        }

        Vec3f pos        = EngineParser::ParseVec3f(tags[CAMERA_TAG_POSITION]);
        Vec3f lookAt     = EngineParser::ParseVec3f(tags[CAMERA_TAG_LOOK_AT]);
        Vec3f up         = EngineParser::ParseVec3f(tags[CAMERA_TAG_UP]);
        Vec3f projection = EngineParser::ParseProjection(tags[CAMERA_TAG_PROJECTION]);
        Vec3f direction  = Vec3f::Normalize(lookAt - pos);

        // Set the position, the lookAt point, the up vector and the projection of the camera.
        res->SetPosition(pos);
        res->SetLookAt(lookAt);
        res->SetUp(up);
        res->SetProjection(projection);
        res->SetDirection(direction);
        res->InitSphereCoords(pos.GetX(),pos.GetY());

#ifndef NDEBUG
        std::cout << "Camera created!" << std::endl;
        std::cout << "Position: " << pos << std::endl;
        std::cout << "Look at: " << lookAt << std::endl;
        std::cout << "Up: " << up << std::endl;
        std::cout << "Projection: " << projection << std::endl;
        std::cout << "Direction: " << direction << std::endl;
        std::cout << "Radius: " << res->mRadius << std::endl;
#endif


        return res;
    }

    /*
    * //////////////////////////////
    * // Setters
    * //////////////////////////////
    */

    void Camera::SetPosition    (const Vec3f &position)   { mPosition = position; }
    void Camera::SetLookAt      (const Vec3f &lookAt)     { mLookAt = lookAt; }
    void Camera::SetUp          (const Vec3f &up)         { mUp = up; }
    void Camera::SetProjection  (const Vec3f &projection) { mProjection = projection; }
    void Camera::SetRadius      (float radius)            { mRadius = radius; }

    /*
    * //////////////////////////////
    * // Getters
    * //////////////////////////////
    */

    Vec3f Camera::GetPosition()   { return mPosition; }
    Vec3f Camera::GetLookAt()     { return mLookAt; }
    Vec3f Camera::GetUp()         { return mUp; }
    Vec3f Camera::GetProjection() { return mProjection; }

    /*
    * //////////////////////////////
    * // Instance methods
    * //////////////////////////////
    */

    void Camera::Move(CameraMovement move) {
        switch (move) {
            case CameraMovement::FORWARD:
                mPosition += mDirection * CAMERA_SPEED;
                mLookAt = mPosition + mDirection;
                break;
            case CameraMovement::BACKWARD:
                mPosition -= mDirection * CAMERA_SPEED;
                mLookAt = mPosition + mDirection;
                break;
            case CameraMovement::LEFT:
                mPosition -= Vec3f::Normalize(Vec3f::Cross(mDirection , mUp)) * CAMERA_SPEED;
                mLookAt = mPosition + mDirection;
                break;
            case CameraMovement::RIGHT:
                mPosition += Vec3f::Normalize(Vec3f::Cross(mDirection , mUp)) * CAMERA_SPEED;
                mLookAt = mPosition + mDirection;
                break;
            default:
                break;
        }

#ifndef NDEBUG
        std::cout << "Position: " << mPosition << std::endl;
        std::cout << "LookAt: " << mLookAt << std::endl;
        std::cout << "Direction: " << mDirection << std::endl;
        std::cout << "Up: " << mUp << std::endl;
#endif
    }

    void Camera::Rotate(const float x, const float y) {
        if (mFirstMouse)
        {
            mLastX = x;
            mLastY = y;
            mFirstMouse = false;
        }

        float xoffset = x - mLastX;
        float yoffset = mLastY - y;
        mLastX = x;
        mLastY = y;

        mAlpha += xoffset * CAMERA_SENSITIVITY;
        mBeta  += yoffset * CAMERA_SENSITIVITY;

        // Make sure that when beta is out of bounds, screen doesn't get flipped
        mBeta = std::max(-1.5f, std::min(1.5f, mBeta));

        cg_math::Vec3f direction = cg_math::Vec3f::CreateCartesianFromSphere(mAlpha, mBeta, mRadius);
        mDirection = cg_math::Vec3f::Normalize(direction);
        mLookAt = mPosition + mDirection;

#ifndef NDEBUG
        std::cout << "Alpha: " << mAlpha << std::endl;
        std::cout << "Beta: " << mBeta << std::endl;
        std::cout << "Radius: " << mRadius << std::endl;
        std::cout << "Position: " << mPosition << std::endl;
        std::cout << "LookAt: " << mLookAt << std::endl;
        std::cout << "Direction: " << mDirection << std::endl;
        std::cout << "Up: " << mUp << std::endl;
#endif

    }

    void Camera::InitSphereCoords(const float x, const float y) {
        mRadius = Vec3f::Norm(mPosition);
        // The alpha angle is the angle between the x-axis and the projection of the position vector on the xz plane.
        //mAlpha = acos(y / mRadius);
        // The beta angle is the angle between the z-axis and the projection of the position vector on the xz plane.
        //mBeta = atan2(y, x);
    }


    void Camera::SetDirection(const Vec3f &front) {
        mDirection = front;
    }
} // cg_engine