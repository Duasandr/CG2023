//
// Created by Sandro Duarte on 19/03/2023.
//
#ifdef __APPLE__
#include <glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif
#include "world/Window.h"
#include "Parser.h"

namespace cg_engine {

    /**
     * Creates a Window from an xml tag
     * @param tag
     * @return
     */
    Window *Window::Create(tinyxml2::XMLElement *tag) {
        Window *res = new Window();

        if(tag) {
            res->mWidth = Parser::ParseInt(tag->Attribute("width"));
            res->mHeight = Parser::ParseInt(tag->Attribute("height"));
        }

        return res;
    }

    int Window::getWidth() const {
        return mWidth;
    }

    int Window::getHeight() const {
        return mHeight;
    }
} // cg_engine