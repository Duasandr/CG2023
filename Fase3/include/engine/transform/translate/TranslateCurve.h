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
    class TranslateCurve: public Transform {
    public:
        /**
         * @brief Default constructor.
         * @details It sets the vector to (0.0f, 0.0f, 0.0f).
         */
        TranslateCurve() = default;
        /**
         * @brief Constructor that takes the vector of translation.
         * @details It sets the vector to the given value.
         * @param x X coordinate of the vector.
         * @param y Y coordinate of the vector.
         * @param z Z coordinate of the vector.
         */
        TranslateCurve(float time, bool align);

        /**
         * @brief Apply method is used to apply the transformation.
         * @details It is a virtual method that is implemented in the derived classes. It calls the glTranslatef function.
         */
        void Apply() override;
    private:

        void getGlobalCatmullRomPoint(float gt, float *pos, float *deriv);
        void getCatmullRomPoint(float t, float *p0, float *p1, float *p2, float *p3, float *pos, float *deriv);

        float mTime;
        bool mAlign;
        std::vector<cg_math::Vec3f> mPoints;
    };

} // cg_engine

#endif //ENGINE_TRANSLATE_H
