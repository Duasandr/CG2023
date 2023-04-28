//
// Created by Sandro Duarte on 19/03/2023.
//
#include "world/Window.h"
#include "utils/EngineParser.h"

/**
 * cg_engine namespace contains all the classes and functions of the engine
 */
namespace cg_engine {
    using cg_utils::Parser;

    Window *Window::Create(tinyxml2::XMLElement *tag) {
        auto *res = new Window();

        // Parse the width and height of the window
        if(tag) {
            res->mWidth = EngineParser::ParseInt(tag->Attribute("width"));
            res->mHeight = EngineParser::ParseInt(tag->Attribute("height"));
        }

        return res;
    }

    int Window::getWidth() const { return mWidth; }
    int Window::getHeight() const { return mHeight; }
} // cg_engine