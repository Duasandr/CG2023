//
// Created by Sandro Duarte on 19/03/2023.
//

#ifndef ENGINE_WINDOW_H
#define ENGINE_WINDOW_H
#include "utils/tinyxml2.h"

namespace cg_engine {
    /**
     * @brief Represents a window of the world
     * @see World
     */
    class Window {
    public:
        /**
         * @brief Copy constructor
         * @details explicitly deleted copy constructor to avoid copying
         * @param window
         */
        Window(const Window &window) = delete;
        /**
         * @brief Move constructor
         * @details explicitly deleted move constructor to avoid moving
         * @param window
         */
        Window(Window &&window) = delete;
        /**
         * @brief Virtual destructor.
         * @details This destructor is used to free the memory allocated by the window.
         */
        virtual ~Window() = default;

        /**
         * Creates a Window from an .xml file.
         * @param pathToFile
         * @return A pointer to the created window
         */
        static Window *Create(tinyxml2::XMLElement *tag);

        /**
         * @brief Get the width of the window
         * @return The width of the window
         */
        int getWidth() const;
        /**
         * @brief Get the height of the window
         * @return The height of the window
         */
        int getHeight() const;

    private:
        /**
         * @brief Default constructor
         * @details This constructor is used to create an empty window.
         * @note This constructor is not intended to be used directly. Use the static method Window::Create() instead.
         */
        Window() = default;

        /**
         * @brief Width of the window
        */
        int mWidth;
        /**
         * @brief Height of the window
        */
        int mHeight;

    };

} // cg_engine

#endif //ENGINE_WINDOW_H
