//
// Created by Sandro Duarte on 19/03/2023.
//

#ifndef ENGINE_WORLD_H
#define ENGINE_WORLD_H
#include <vector>
#include "Camera.h"
#include "Group.h"
#include "Window.h"

namespace cg_engine {

    class World {
    public:
        World() = default;
        virtual ~World() = default;

        static World* Create(const char *pathToFile);

        void LoadGroups();
        void Draw();

        Window &Window();
        Camera &Camera();
    private:
        tinyxml2::XMLDocument mConfigFile;
        cg_engine::Window *mWindow;
        cg_engine::Camera *mCamera;
        std::vector<cg_engine::Group*> mGroups;

        static void LoadGroups(World *res, tinyxml2::XMLElement *world_tag);
    };

} // cg_engine

#endif //ENGINE_WORLD_H
