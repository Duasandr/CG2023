//
// Created by Sandro Duarte on 19/03/2023.
//
#ifdef __APPLE__
#include <glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif
#include "world/Group.h"
#include "transform/Transform.h"

namespace cg_engine {
    using std::vector;
    using tinyxml2::XMLElement;

    Group::Group() {
        mTransforms = vector<Transform*>();
        mModels = vector<Model*>();
        mChildGroup = nullptr;
    }

    Group *Group::Create(tinyxml2::XMLElement *block) {
        auto *res = new Group();

        XMLElement *transform_block = block->FirstChildElement("transform");
        if(transform_block) {
            for (XMLElement *transform_tag = transform_block->FirstChildElement();
                 transform_tag != nullptr; transform_tag = transform_tag->NextSiblingElement()) {
                res->mTransforms.push_back(Transform::Create(transform_tag));
            }
        }

        XMLElement *models_block = block->FirstChildElement("models");
        if(models_block) {
            for (XMLElement *model_tag = models_block->FirstChildElement("model");
                 model_tag != nullptr; model_tag = model_tag->NextSiblingElement("model")) {
                res->mModels.push_back(Model::Create(model_tag->Attribute("file")));
            }
        }

        // Create child group if it exists
        Group **root = &res->mChildGroup;
        for (XMLElement *group_tag = block->FirstChildElement("group"); group_tag != nullptr; group_tag = group_tag->NextSiblingElement("group")) {
            *root = Create(group_tag);
            root = &(*root)->mChildGroup;
        }

        return res;
    }

    void Group::Draw() {
        glPushMatrix();

        // Apply all transforms to the group
        for (auto &transform: mTransforms) {
            if(transform) {
                transform->Apply();
            }
        }

        // Draw all models in the group
        for (auto &model: mModels) {
            if (model) {
                model->Draw();
            }
        }

        // Draw child group if it exists
        if(mChildGroup) {
            mChildGroup->Draw();
        }

        glPopMatrix();
    }
} // cd_engine