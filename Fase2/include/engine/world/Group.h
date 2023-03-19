//
// Created by Sandro Duarte on 19/03/2023.
//

#ifndef ENGINE_GROUP_H
#define ENGINE_GROUP_H
#include "tinyxml2.h"
#include "world/model/Model.h"
#include "transform/Transform.h"
#include <vector>

namespace cg_engine {

    /**
     * Group class that abstracts hierarchy of Models to be drawn.
     * Acts as a linked list.
     */
    class Group {
    public:
        Group() = default;
        virtual ~Group() = default;

        static Group *Create(tinyxml2::XMLElement *block);

        void Draw();

    private:
        std::vector<cg_engine::Transform*> mTransforms;
        std::vector<cg_engine::Model*> mModels;
        Group *mChildGroup;
    };

} // cd_engine

#endif //ENGINE_GROUP_H
