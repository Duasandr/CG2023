//
// Created by Sandro Duarte on 19/03/2023.
//
#include <iostream>
#include "world/Window.h"
#include "world/World.h"
#include "tinyxml2.h"

namespace cg_engine {
    using std::cerr;
    using std::endl;
    using tinyxml2::XMLDocument;
    using tinyxml2::XMLElement;

    World *World::Create(const char *pathToFile) {
        World *res = new World();

        if(res->mConfigFile.LoadFile(pathToFile) != tinyxml2::XML_SUCCESS) {
            cerr << "Error opening XML configuration file." << endl;
            return nullptr;
        }

        XMLElement *world_tag = res->mConfigFile.FirstChildElement("world");

        res->mWindow = Window::Create(world_tag->FirstChildElement("window"));

        res->mCamera = Camera::Create(world_tag->FirstChildElement("camera"));

        return res;
    }

    void World::LoadGroups() {
        XMLElement *world_tag = mConfigFile.FirstChildElement("world");

        for (XMLElement *group_tag = world_tag->FirstChildElement("group"); group_tag != nullptr; group_tag = group_tag->NextSiblingElement("group")) {
            mGroups.push_back(Group::Create(group_tag));
        }
    }

    Camera &World::Camera() {
        return *mCamera;
    }

    Window &World::Window() {
        return *mWindow;
    }

    void World::Draw() {
        for (auto &group: mGroups) {
            group->Draw();
        }
    }
} // cg_engine