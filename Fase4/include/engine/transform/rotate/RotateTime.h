//
// Created by Sandro Duarte on 26/05/2023.
//

#ifndef ENGINE_ROTATETIME_H
#define ENGINE_ROTATETIME_H
#include "Transform.h"
#include "Vec3f.h"

namespace cg_engine {
    class RotateTime : public Transform {
    public:
        /**
         * @brief Default constructor.
         */
        RotateTime();

        /**
         * @brief Constructor that takes the angle and the vector of rotation.
         * @param angle Angle of rotation.
         * @param x X component of the vector of rotation.
         * @param y Y component of the vector of rotation.
         * @param z Z component of the vector of rotation.
         */
        RotateTime(float time, float x, float y, float z);

        /**
         * @brief Apply method is used to apply the transformation.
         * @details It is a virtual method that is implemented in the derived classes. It calls the glRotatef function.
         */
        void Apply() override;

    private:
        /**
         * @brief mVector is the vector of rotation.
         */
        cg_math::Vec3f mVector;
        /**
         * @brief Duration of rotation.
         */
        float mTime;
        float mCurrentAngle;

    };
}


#endif //ENGINE_ROTATETIME_H
