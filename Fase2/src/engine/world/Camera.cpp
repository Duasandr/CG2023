//
// Created by Sandro Duarte on 10/03/2023.
//
#include "world/Camera.h"
#include "Parser.h"

namespace cg_engine {
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
        mAlpha = 0.0f;
        mBeta = 0.0f;
        mRadius = 0.0f;
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


        return res;
    }

    void Camera::SetPosition(float x, float y, float z) {
        mPosition = Vec3f(x, y, z);

        // The radius is the norm of the position vector.
        mRadius = mPosition.Norm();
        // The alpha angle is the angle between the x-axis and the projection of the position vector on the xz plane.
        mAlpha = acos(y / mRadius);
        // The beta angle is the angle between the z-axis and the projection of the position vector on the xz plane.
        mBeta = atan2(y, x);
    }

    void Camera::SetLookAt(float x, float y, float z) { mLookAt = Vec3f(x, y, z); }

    void Camera::SetUp(float x, float y, float z) { mUp = Vec3f(x, y, z); }

    void Camera::SetProjection(float fov, float near, float far) { mProjection = Vec3f(fov, near, far); }

    Vec3f Camera::GetPosition() const { return mPosition; }

    Vec3f Camera::GetLookAt() const { return mLookAt; }

    Vec3f Camera::GetUp() const { return mUp; }

    Vec3f Camera::GetProjection() const { return mProjection; }

    void Camera::FreeMoveLeft() {
        mAlpha -= 0.1;

        mPosition.SphereToCartesian(mAlpha, mBeta, mRadius);
    }

    void Camera::FreeMoveRight() {
        mAlpha += 0.1;

        mPosition.SphereToCartesian(mAlpha, mBeta, mRadius);
    }

    void Camera::FreeMoveUp() {
        mBeta += 0.1;

        // approximately PI/2
        if(mBeta > 1.5) {
            mBeta = 1.5;
        }

        mPosition.SphereToCartesian(mAlpha, mBeta, mRadius);
    }

    void Camera::FreeMoveDown() {
        mBeta -= 0.1;

        // approximately PI/2
        if(mBeta < -1.5) {
            mBeta = -1.5;
        }
        
        mPosition.SphereToCartesian(mAlpha, mBeta, mRadius);
    }

    void Camera::FreeMoveBack() {
        mRadius += 1;

        mPosition.SphereToCartesian(mAlpha, mBeta, mRadius);
    }

    void Camera::FreeMoveFront() {
        mRadius -= 1;

        mPosition.SphereToCartesian(mAlpha, mBeta, mRadius);
    }

    void Camera::LookLeft() {
        mLookAt.SetX(mLookAt.GetX()+1);
    }

    void Camera::LookRight() {
        mLookAt.SetX(mLookAt.GetX()-1);
    }

    void Camera::LookFront() {
        mLookAt.SetZ(mLookAt.GetZ()-1);
    }

    void Camera::LookBack() {
        mLookAt.SetZ(mLookAt.GetZ()+1);
    }


} // cg_engine