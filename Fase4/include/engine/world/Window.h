//
// Created by Sandro Duarte on 19/03/2023.
//

#ifndef ENGINE_WINDOW_H
#define ENGINE_WINDOW_H
#include "utils/tinyxml2.h"
#include <string>

namespace cg_engine {
    /**
     * @brief Represents a window of the world
     * @see World
     */
    class Window {
    public:
        /**
         * @brief Default constructor
         * @details This constructor is used to create a window with the default values.
         */
        Window() = default;
        Window(int width, int height);
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
         * @brief Get the width of the window
         * @return The width of the window
         */
        int getWidth() const;
        /**
         * @brief Get the height of the window
         * @return The height of the window
         */
        int getHeight() const;
        /**
         * @brief Get the title of the window
         * @return The title of the window
         */
        std::string getTitle() const;
        /**
         * @brief Set the title of the window
         * @param title The title of the window
         */
        void setTitle(const std::string &title);

    private:
        /**
         * @brief Width of the window
        */
        int mWidth;
        /**
         * @brief Height of the window
        */
        int mHeight;

        /**
         * @brief Title of the window
        */
        std::string mTitle;

    };

} // cg_engine

#endif //ENGINE_WINDOW_H
