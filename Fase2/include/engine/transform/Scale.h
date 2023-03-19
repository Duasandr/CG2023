//
// Created by Sandro Duarte on 19/03/2023.
//

#ifndef ENGINE_SCALE_H
#define ENGINE_SCALE_H
#include "Transform.h"
#include "Vec3f.h"

namespace cg_engine {

    class Scale: public Transform {
    public:
        Scale() = default;
        Scale(float factor);

        void Apply() override;
    private:
        float mFactor;
    };

} // cg_engine

#endif //ENGINE_SCALE_H
