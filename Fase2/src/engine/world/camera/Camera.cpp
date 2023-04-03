//
// Created by Sandro Duarte on 10/03/2023.
//
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
        mCameraType = new Spherical(*this);
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

        // Set the camera type. By default, it is spherical.
        res->SetCameraType(new Spherical(*res));

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
        mCameraType->Move(*this, option);
    }

    void Camera::SwitchType() {
        if (mCameraType->GetType() == CameraType::SPHERICAL) {
            mCameraType = new FirstPerson();
        } else {
            mCameraType = new Spherical(*this);
        }
    }


} // cg_engine