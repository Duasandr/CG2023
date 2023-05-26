//
// Created by Sandro Duarte on 19/03/2023.
//
#include "world/Window.h"

#include <utility>
#include "utils/EngineParser.h"

/**
 * cg_engine namespace contains all the classes and functions of the engine
 */
namespace cg_engine {
    Window::Window(int width, int height) {
        mWidth = width;
        mHeight = height;
    }

    int Window::getWidth() const { return mWidth; }
    int Window::getHeight() const { return mHeight; }

    std::string Window::getTitle() const {
        return {mTitle};
    }

    void Window::setTitle(const std::string &title) {
        mTitle = title;
    }

} // cg_engine