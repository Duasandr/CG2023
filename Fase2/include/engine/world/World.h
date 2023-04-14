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

    /**
     * @brief Represents a world
     * @details A world is a collection of groups, a camera and a window
     * @note This class is not intended to be instantiated directly. Use the static method World::Create() instead.
     */
    class World {
    public:
        /**
         * @brief Default destructor
         * @details This destructor is used to free the memory allocated by the world.
         */
        virtual ~World() = default;
        /**
         * @brief Create a world from a configuration file
         * @param pathToFile Path to the configuration file
         * @return A pointer to the created world
         */
        static World* Create(const char *pathToFile);

        /**
         * @brief Load the groups from the configuration file
         *
         */
        void LoadGroups();
        /**
         * @brief Draw the world
         * @details This method is used to draw the world. It will draw all the groups.
         */
        void Draw();

        /**
         * @brief Get the window
         * @details This method is used to get the window of the world.
         * @return A reference to the window
         */
        Window &Window();
        /**
         * @brief Get the camera
         * @details This method is used to get the camera of the world.
         * @return A reference to the camera
         */
        Camera &Camera();
    private:
        /**
         * @brief Default constructor
         * @details This constructor is used to create an empty world.
         * @note This constructor is not intended to be used directly. Use the static method World::Create() instead.
         */
        World() = default;

        /**
         * @brief Configuration file
         * @details This XML document contains the configuration of the world.
         */
        tinyxml2::XMLDocument mConfigFile;
        /**
         * @brief Window of the world
         */
        cg_engine::Window *mWindow;
        /**
         * @brief Camera of the world
         */
        cg_engine::Camera *mCamera;
        /**
         * @brief List of groups
         * @details This vector contains all the groups that will be drawn by the world.
         */
        std::vector<cg_engine::Group*> mGroups;
    };

} // cg_engine

#endif //ENGINE_WORLD_H
