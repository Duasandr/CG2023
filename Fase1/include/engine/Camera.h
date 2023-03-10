//
// Created by Sandro Duarte on 10/03/2023.
//

#ifndef ENGINE_CAMERA_H
#define ENGINE_CAMERA_H
#include <Vec3f.h>

namespace cg_engine {
    class Camera {
    public:
        Camera();
        virtual ~Camera();

        void SetPosition(float x, float y, float z);
        void SetLookAt(float x, float y, float z);
        void SetUp(float x, float y, float z);
        void SetProjection(float fov, float near, float far);

        void FreeMoveLeft();
        void FreeMoveRight();
        void FreeMoveUp();
        void FreeMoveDown();

        void FreeMoveFront();
        void FreeMoveBack();

        cg_math::Vec3f GetPosition() const;
        cg_math::Vec3f GetLookAt() const;
        cg_math::Vec3f GetUp() const;
        cg_math::Vec3f GetProjection() const;

    private:
        cg_math::Vec3f mPosition;
        cg_math::Vec3f mLookAt;
        cg_math::Vec3f mUp;
        cg_math::Vec3f mProjection;

        float mAlpha;
        float mBeta;
        float mRadius;

        void SphereToCartesian();
    };

} // cg_engine

#endif //ENGINE_CAMERA_H
