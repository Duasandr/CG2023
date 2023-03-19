//
// Created by Sandro Duarte on 19/03/2023.
//

#ifndef ENGINE_WINDOW_H
#define ENGINE_WINDOW_H
#include "tinyxml2.h"

namespace cg_engine {

    class Window {
    public:
        Window() = default;
        virtual ~Window() = default;

        /**
         * Creates a Window from an .xml file.
         * @param pathToFile
         * @return
         */
        static Window *Create(tinyxml2::XMLElement *tag);

        int getWidth() const;
        int getHeight() const;

    private:
        int mWidth;
        int mHeight;

    };

} // cg_engine

#endif //ENGINE_WINDOW_H
