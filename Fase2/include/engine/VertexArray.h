//
// Created by Sandro Duarte on 19/03/2023.
//

#ifndef ENGINE_VERTEXARRAY_H
#define ENGINE_VERTEXARRAY_H

class VertexBuffer;

namespace cg_engine {

    /**
     * Vertex Array class that abstract a vao.
     * The vertices are 3 floats representing a 3D coordinate.
     */
    class VertexArray {
    public:
        VertexArray() = default;

        /**
         * Sets the vertices. Reads values from a .3d file.
         * @param pathToFile
         * @throws std::exception when file not found
        */
        void SetVertices(const char* pathToFile);

        /**
         * Copies data to a VertexBuffer.
         * @param vertexBuffer
        */
        void CopyData(VertexBuffer &vertexBuffer) const;

        /**
         * Returns the number of vertices (number of (x,y,z) values) of the array.
         * @return
        */
        int GetVertexCount() const;

    private:

        int mVertexCount;
        float *mVertices;
    };

} // cg_engine

#endif //ENGINE_VERTEXARRAY_H
