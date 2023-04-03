//
// Created by Sandro Duarte on 19/03/2023.
//

#ifndef ENGINE_TRANSFORM_H
#define ENGINE_TRANSFORM_H
#include "tinyxml2.h"

/**
 * @brief cg_engine namespace contains all the classes and functions of the engine.
 */
namespace cg_engine {

    /**
     * @brief Transform class is the base class for all the transformations.
     * @details It is an abstract class that contains the virtual method Apply. This method is used to apply the transformation.
     */
    class Transform {
    public:
        /**
         * @brief Default constructor.
         */
        Transform() = default;
        /**
         * @brief Default destructor.
         */
        virtual ~Transform() =default;

        /**
         * @brief Create method is used to create a new transformation. Factory method.
         * @details It is a static method that creates a new transformation based on the XML tag.
         * @param tag XML tag that contains the information about the transformation.
         * @return A pointer to the new transformation.
         */
        static Transform *Create(tinyxml2::XMLElement *tag);

        /**
         * @brief Apply method is used to apply the transformation.
         * @details It is a virtual method that is implemented in the derived classes.
         */
        virtual void Apply() = 0;
    };

} // cg_engine

#endif //ENGINE_TRANSFORM_H
