//
// Created by Sandro Duarte on 10/03/2023.
//

#ifndef ENGINE_MODEL_H
#define ENGINE_MODEL_H
#include <fstream>
#include <cstdint>
#include <VertexBuffer.h>
#include <VertexArray.h>

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
        static Model *Create(const char *path);

        void Draw() const;

        /**
         * Returns the current vertex count of the model
         * @return Number of vertices
         */
        unsigned int GetVertexCount() const;

        const float *GetVertices() const;


    private:
        Model() = default;

        /**
         * Constructs a Model object from a .3d file.
         * @param pathToFile
        */
        Model(const char *pathToFile);

        VertexArray mVertexArray;
        VertexBuffer mVertexBuffer;
    };

} // cg_engine

#endif //ENGINE_MODEL_H
