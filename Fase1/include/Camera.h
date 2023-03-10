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

    private:
        cg_math::Vec3f mPosition;
        cg_math::Vec3f mLookAt;
        cg_math::Vec3f mUp;
        cg_math::Vec3f mProjection;
    };

} // cg_engine

#endif //ENGINE_CAMERA_H
