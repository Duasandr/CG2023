//
// Created by Sandro Duarte on 19/03/2023.
//

#ifndef ENGINE_TRANSLATE_H
#define ENGINE_TRANSLATE_H
#include "Transform.h"
#include "Vec3f.h"

namespace cg_engine {

    /**
     * @brief Translate class.
     * @details It is a derived class of Transform. It contains the vector of translation.
     */
    class Translate: public Transform {
    public:
        /**
         * @brief Default constructor.
         * @details It sets the vector to (0.0f, 0.0f, 0.0f).
         */
        Translate() = default;
        /**
         * @brief Constructor that takes the vector of translation.
         * @details It sets the vector to the given value.
         * @param x X coordinate of the vector.
         * @param y Y coordinate of the vector.
         * @param z Z coordinate of the vector.
         */
        Translate(float x, float y, float z);

        /**
         * @brief Apply method is used to apply the transformation.
         * @details It is a virtual method that is implemented in the derived classes. It calls the glTranslatef function.
         */
        void Apply() override;
    private:
        /**
         * @brief Vector of translation.
         */
        cg_math::Vec3f mVector;
    };

} // cg_engine

#endif //ENGINE_TRANSLATE_H
