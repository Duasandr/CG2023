//
// Created by Sandro Duarte on 19/03/2023.
//

#ifndef ENGINE_TRANSLATE_CURVE_H
#define ENGINE_TRANSLATE_CURVE_H
#include "Transform.h"
#include "Vec3f.h"
#include "Mat.h"

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

        cg_math::Vec3f GetCatmullRomPoint(float gt);
        cg_math::Vec3f GetCatmullRomDerivative(float gt);

        void Align(float t);

        /**
         * @brief Apply method is used to apply the transformation.
         * @details It is a virtual method that is implemented in the derived classes. It calls the glTranslatef function.
         */
        void Apply() override;

        void AddPoint(const cg_math::Vec3f &point);

    private:
        float ComputeIndices(float gt);

        float mTime;
        bool mAlign;
        int mCurrentIndices[4];
        cg_math::Vec3f mPrevY;
        std::vector<cg_math::Vec3f> mPoints;

    };

} // cg_engine

#endif //ENGINE_TRANSLATE_CURVE_H
