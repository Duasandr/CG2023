//
// Created by Sandro Duarte on 19/03/2023.
//

#ifndef ENGINE_GROUP_H
#define ENGINE_GROUP_H
#include "utils/tinyxml2.h"
#include "world/model/Model.h"
#include "transform/Transform.h"
#include <vector>

/**
 * @brief Namespace for the cg_engine library
 * @details This namespace contains all the classes and functions of the cg_engine library.
 */
namespace cg_engine {

    /**
     * @brief Group of models and transformations
     * @details This class is used to group models and transformations in a linked list structure.
     * @note This class is not intended to be instantiated directly. Use the static method Group::Create() instead.
     */
    class Group {
    public:
        /**
         * @brief Default destructor
         * @details This destructor is used to free the memory allocated by the group.
         */
        virtual ~Group() = default;

        /**
         * @brief Create a group from an XML block
         * @details This method is used to create a group from an XML block.
         * @param block XML block containing the group information
         * @return A pointer to the created group
         */
        static Group *Create(tinyxml2::XMLElement *block);

        /**
         * @brief Draw the group
         * @details This method is used to draw the group. It will draw all the models and transformations.
         */
        void Draw();

    private:
        /**
         * @brief Default constructor
         * @details This constructor is used to create an empty group.
         * @note This constructor is not intended to be used directly. Use the static method Group::Create() instead.
         */
        Group();

        /**
         * @brief List of transformations
         * @details This vector contains all the transformations that will be applied to the group.
         */
        std::vector<Transform*> mTransforms;
        /**
         * @brief List of models
         * @details This vector contains all the models that will be drawn by the group.
         */
        std::vector<Model*> mModels;
        /**
         * @brief Child groups
         * @details This vector contains all the child groups of the group.
         */
        std::vector<Group*> mChildGroups;
    };

} // cd_engine

#endif //ENGINE_GROUP_H
