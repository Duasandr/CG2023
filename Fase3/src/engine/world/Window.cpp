//
// Created by Sandro Duarte on 19/03/2023.
//
#include "world/Window.h"
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

} // cg_engine