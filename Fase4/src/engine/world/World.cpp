//
// Created by Sandro Duarte on 19/03/2023.
//
#include <iostream>
#include "world/Window.h"
#include "world/World.h"
#include "EngineParser.h"

namespace cg_engine {
    using std::cerr;
    using std::endl;
    using tinyxml2::XMLDocument;
    using tinyxml2::XMLElement;

    World *World::Create(const char *pathToFile) {
        auto *res = new World();

        if(res->mConfigFile.LoadFile(pathToFile) != tinyxml2::XML_SUCCESS) {
            cerr << "Error opening XML configuration file." << endl;
            return nullptr;
        }

        XMLElement *world_tag = res->mConfigFile.FirstChildElement("world");

        res->mWindow = EngineParser::ParseWindow(world_tag->FirstChildElement("window"));

        res->mCamera = Camera::Create(world_tag->FirstChildElement("camera"));

        XMLElement *lights_block = world_tag->FirstChildElement("lights");

        if (lights_block) {

            for (XMLElement *light_tag = lights_block->FirstChildElement("light");
                 light_tag != nullptr; light_tag = light_tag->NextSiblingElement("light")) {
                res->mLights.push_back(EngineParser::ParseLights(light_tag));
            }
        }

        return res;
    }

    void World::LoadGroups() {
        XMLElement *world_tag = mConfigFile.FirstChildElement("world");

        // Load groups from XML file into the world object (mGroups) and create them in the GPU memory (OpenGL) as well.
        // This is done by calling the Group::Create() method.
        // The Group::Create() method will return a pointer to a Group object that will be stored in the mGroups vector.
        // The Group::Create() method will also create the group in the GPU memory (OpenGL) and store the group's ID in the Group object.
        for (XMLElement *group_tag = world_tag->FirstChildElement("group"); group_tag != nullptr; group_tag = group_tag->NextSiblingElement("group")) {
            // Create a new group and store it in the mGroups vector.
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
            if (group) {
                group->Draw();
            }
        }
        for(auto light: mLights) {
            if(light) {
                light->TurnOn();
            }
        }
    }

    int World::GetLightsSize() const {
        return mLights.size();
    }

    std::vector<Light*> *World::GetLights() {
        return &mLights;
    }
} // cg_engine