//
// Created by Sandro Duarte on 19/03/2023.
//

#ifndef ENGINE_ROTATE_H
#define ENGINE_ROTATE_H
#include "Transform.h"
#include "Vec3f.h"

namespace cg_engine {

    class Rotate: public Transform {
    public:
        Rotate() = default;
        Rotate(float angle, float x, float y, float z);

        void Apply() override;
    private:
        cg_math::Vec3f mVector;
        float mAngle;
    };

} // cg_engine

#endif //ENGINE_ROTATE_H
