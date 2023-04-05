//
// Created by Sandro Duarte on 10/03/2023.
//
#ifdef __APPLE__
#include <glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif
#include "world/camera/Camera.h"
#include "world/camera/Spherical.h"
#include "Parser.h"
#include "world/camera/FirstPerson.h"

namespace cg_engine {
    using cg_utils::Parser;
    using tinyxml2::XMLElement;
    using cg_math::Vec3f;

    /**
     * @brief Default constructor.
     * @details It initializes the position, the lookAt point, the up vector and the projection vector.
     * It also initializes the radius, the alpha and the beta angles.
     */
    Camera::Camera() {
        mPosition = Vec3f();
        mLookAt = Vec3f();
        mUp = Vec3f();
        mProjection = Vec3f();
        mFirstMouse = true;
    }

    Camera *Camera::Create(tinyxml2::XMLElement *block) {
        auto *res = new Camera();

        // Parse the position of the camera from the XML block.
        XMLElement *tag = block->FirstChildElement("position");

        // Set the position of the camera.
        res->SetPosition(Parser::ParseFloat(tag->Attribute("x")),
                               Parser::ParseFloat(tag->Attribute("y")),
                               Parser::ParseFloat(tag->Attribute("z")));

        // Parse the lookAt point of the camera from the XML block.
        tag = block->FirstChildElement("lookAt");

        // Set the lookAt point of the camera.
        res->SetLookAt(Parser::ParseFloat(tag->Attribute("x")),
                               Parser::ParseFloat(tag->Attribute("y")),
                               Parser::ParseFloat(tag->Attribute("z")));

        // Parse the up vector of the camera from the XML block.
        tag = block->FirstChildElement("up");

        // Set the up vector of the camera.
        res->SetUp(Parser::ParseFloat(tag->Attribute("x")),
                       Parser::ParseFloat(tag->Attribute("y")),
                       Parser::ParseFloat(tag->Attribute("z")));


        // Parse the projection of the camera from the XML block.
        tag = block->FirstChildElement("projection");

        // Set the projection of the camera.
        res->SetProjection(Parser::ParseFloat(tag->Attribute("fov")),
                                 Parser::ParseFloat(tag->Attribute("near")),
                                 Parser::ParseFloat(tag->Attribute("far")));

        res->SetFront(cg_math::Vec3f::Normalize(res->mPosition - res->mLookAt));
        res->InitSphereCoords(res->GetPosition().GetX(), res->GetPosition().GetY());
        // Set the camera type. By default, it is spherical.
        //res->SetCameraType(new Spherical(*res));

        return res;
    }

    void Camera::SetPosition(float x, float y, float z) {
        mPosition = Vec3f(x, y, z);
    }

    // Setters

    void Camera::SetLookAt(float x, float y, float z) { mLookAt = Vec3f(x, y, z); }

    void Camera::SetUp(float x, float y, float z) { mUp = Vec3f(x, y, z); }

    void Camera::SetProjection(float fov, float near, float far) { mProjection = Vec3f(fov, near, far); }

    void Camera::SetCameraType(CameraType *cameraType) {
        delete mCameraType;
        mCameraType = cameraType;
    }

    // Getters

    /**
     * @brief Get the position of the camera.
     * @details It returns the position of the camera. It is a const method.
     * @return The position of the camera. It is a const reference to a Vec3f.
     */
    Vec3f const &Camera::GetPosition() const { return mPosition; }

    Vec3f &Camera::GetPosition() { return mPosition; }

    Vec3f &Camera::GetLookAt() { return mLookAt; }

    Vec3f &Camera::GetUp() { return mUp; }

    Vec3f &Camera::GetProjection() { return mProjection; }

    void Camera::Move(const unsigned char option) {
        //mCameraType->Move(*this, option);
        switch (option) {
            case 'w':
                mPosition += mFront * 1.5f;
                break;
            case 's':
                mPosition -= mFront * 1.5f;
                break;
            case 'a':
                mPosition -= cg_math::Vec3f::Normalize(cg_math::Vec3f::Cross(mFront , mUp)) * 1.5f;
                break;
            case 'd':
                mPosition += cg_math::Vec3f::Normalize(cg_math::Vec3f::Cross(mFront , mUp)) * 1.5f;
                break;
            default:
                break;
        }
        PositionCamera();
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

        float sensitivity = 0.01f;
        xoffset *= sensitivity;
        yoffset *= sensitivity;

        mAlpha += xoffset;
        mBeta  += yoffset;

        if(mBeta > 1.5f)
            mBeta = 1.5f;
        else if(mBeta < -1.5f)
            mBeta = -1.5f;

        cg_math::Vec3f direction = cg_math::Vec3f::CreateCartesianFromSphere(mAlpha, mBeta, mRadius);
        mFront = cg_math::Vec3f::Normalize(direction);
        PositionCamera();
    }

    void Camera::InitSphereCoords(const float x, const float y) {
        // The radius is the norm of the position vector.
        mRadius = mPosition.Norm();
        // The alpha angle is the angle between the x-axis and the projection of the position vector on the xz plane.
        mAlpha = acos(y / mRadius);
        // The beta angle is the angle between the z-axis and the projection of the position vector on the xz plane.
        mBeta = atan2(y, x);
    }

    void Camera::SwitchType() {
        if (mCameraType->GetType() == CameraType::SPHERICAL) {
            mCameraType = new FirstPerson();
        } else {
            mCameraType = new Spherical(*this);
        }
    }

    void Camera::PositionCamera() {
       mLookAt = mPosition + mFront;
    }

    void Camera::SetFront(const Vec3f &front) {
        mFront = front;
    }

    void Camera::Zoom(float xoffset, float yoffset) {
        float fov = mProjection.GetX() - yoffset;
        if (fov < 1.0f)
            fov = 1.0f;
        if (fov > 45.0f)
            fov = 45.0f;
        mProjection.SetX(fov);
    }


} // cg_engine