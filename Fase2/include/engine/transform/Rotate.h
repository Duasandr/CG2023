//
// Created by Sandro Duarte on 19/03/2023.
//

#ifndef ENGINE_ROTATE_H
#define ENGINE_ROTATE_H
#include "Transform.h"
#include "Vec3f.h"

/**
 * @brief cg_engine namespace contains all the classes and functions of the engine.
 */
namespace cg_engine {

    /**
     * @brief Rotate class is used to rotate the object.
     * @details It is a derived class of Transform. It contains the angle and the vector of rotation.
     */
    class Rotate: public Transform {
    public:
        /**
         * @brief Default constructor.
         */
        Rotate();
        /**
         * @brief Constructor that takes the angle and the vector of rotation.
         * @param angle Angle of rotation.
         * @param x X component of the vector of rotation.
         * @param y Y component of the vector of rotation.
         * @param z Z component of the vector of rotation.
         */
        Rotate(float angle, float x, float y, float z);

        /**
         * @brief Apply method is used to apply the transformation.
         * @details It is a virtual method that is implemented in the derived classes. It calls the glRotatef function.
         */
        void Apply() override;

        // Deleted copy constructor and assignment operator.

        /**
         * @brief Deleted copy constructor.
         * @param other Other Rotate object.
         * @details Deleted copy constructor to avoid copying the object.
         */
        Rotate(const Rotate &) = delete;
        /**
         * @brief Deleted assignment operator.
         * @param other Other Rotate object.
         * @return A reference to the Rotate object.
         * @details Deleted assignment operator to avoid copying the object.
         */
        Rotate(Rotate &&) = delete;
        /**
         * @brief Deleted assignment operator.
         * @param other Other Rotate object.
         * @return A reference to the Rotate object.
         * @details Deleted assignment operator to avoid copying the object.
         */
        Rotate &operator=(const Rotate &) = delete;
    private:
        /**
         * @brief mVector is the vector of rotation.
         */
        cg_math::Vec3f mVector;
        /**
         * @brief mAngle is the angle of rotation.
         */
        float mAngle;
    };

} // cg_engine

#endif //ENGINE_ROTATE_H
