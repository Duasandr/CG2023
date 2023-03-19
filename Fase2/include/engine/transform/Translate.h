//
// Created by Sandro Duarte on 19/03/2023.
//

#ifndef ENGINE_TRANSLATE_H
#define ENGINE_TRANSLATE_H
#include "Transform.h"
#include "Vec3f.h"

namespace cg_engine {

    class Translate: public Transform {
    public:
        Translate() = default;
        Translate(float x, float y, float z);

        void Apply() override;
    private:
        cg_math::Vec3f mVector;
    };

} // cg_engine

#endif //ENGINE_TRANSLATE_H
