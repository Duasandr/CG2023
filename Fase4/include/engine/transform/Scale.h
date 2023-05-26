//
// Created by Sandro Duarte on 19/03/2023.
//

#ifndef ENGINE_SCALE_H
#define ENGINE_SCALE_H
#include "Transform.h"
#include "Vec3f.h"

/**
 * @brief cg_engine namespace contains all the classes and functions of the engine.
 */
namespace cg_engine {

    /**
     * @brief Scale class is used to scale the object.
     * @details It is a derived class of Transform. It contains the factor of scaling.
     */
    class Scale: public Transform {
    public:
        /**
         * @brief Default constructor.
         * @details It sets the factor to 1.0f.
         */
        Scale();
        Scale(float x, float y, float z);
        /**
         * @brief Constructor that takes the factor of scaling.
         * @details It sets the factor to the given value. It is used to scale the object uniformly.
         * explicit keyword is used to avoid implicit conversion. Implicit conversion is when the compiler automatically converts one type to another.
         * @param factor Factor of scaling.
         */
        explicit Scale(float factor);

        /**
         * @brief Apply method is used to apply the transformation.
         * @details It is a virtual method that is implemented in the derived classes. It calls the glScalef function.
         */
        void Apply() override;
    private:
        /**
         * @brief Factor of scaling.
         */
        float mFactor;
        cg_math::Vec3f *mScaleVec;
    };

} // cg_engine

#endif //ENGINE_SCALE_H
