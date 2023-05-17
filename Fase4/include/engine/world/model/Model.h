//
// Created by Sandro Duarte on 10/03/2023.
//

#ifndef ENGINE_MODEL_H
#define ENGINE_MODEL_H
#include <fstream>
#include <cstdint>
#include "VertexBuffer.h"
#include "VertexArray.h"
#include "color/Color.h"
#include <array>

namespace cg_engine {

    /**
     * Model class that abstracts a 3D model for use with opengl
     */
    class Model {
    public:
        virtual ~Model() = default;

        /**
         * Creates a model from a .3d file
         * @param path
         * @return Model object
         * @throws std::exception when file not found
         */
        static Model *Create(const char *path, const char *texturePath);
        static Model *Create(const char *path);

        static unsigned int LoadTexture(const char *path);

        /**
         * Draws Model to screen.
         * Renders the vertex array.
        */
        void Draw() const;
        void SetColor(Color *color);

    private:
        Model();

        /**
         * Constructs a Model object from a .3d file.
         * @param pathToFile
        */
        Model(const char *pathToFile, const char *texturePath);
        Model(const char *pathToFile);

        int mTextureId;

        VertexArray mPositionArray = VertexArray(3);
        VertexArray mNormalArray = VertexArray(3);
        VertexArray mTextureArray = VertexArray(2);

        VertexBuffer mVertexBuffer;
        VertexBuffer mNormalBuffer;
        VertexBuffer mTextureBuffer;

        Color *mColor = new Color();

        void setArrays(const char *pathToFile);
    };

} // cg_engine

#endif //ENGINE_MODEL_H
