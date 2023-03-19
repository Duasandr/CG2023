//
// Created by Sandro Duarte on 19/03/2023.
//
#include <iostream>
#include <fstream>
#include <stdexcept>
#include "VertexArray.h"
#include "VertexBuffer.h"

namespace cg_engine {
    using std::ifstream;
    using std::endl;

    /**
     * Sets the vertices. Reads values from a .3d file.
     * @param pathToFile
     * @throws std::exception when file not found
    */
    void VertexArray::SetVertices(const char *pathToFile) {
        ifstream ifs;
        ifs.open(pathToFile);

        // If file not found
        if (ifs.fail()) {
            throw std::exception();
        }

        // reads first line of the file which is the total vertex count
        ifs >> mVertexCount;

        // a vertex is 3 floats
        const int size = mVertexCount * 3;
        mVertices = new float[size];

        // reads the remaining values from the file into the array
        for (int i = 0; i < size; ++i) {
            ifs >> mVertices[i];
        }

        ifs.close();
    }

    /**
     * Copies data to a VertexBuffer.
     * @param vertexBuffer
    */
    void VertexArray::CopyData(VertexBuffer &vertexBuffer) const {
        vertexBuffer.SetData(mVertices, mVertexCount * sizeof(float) * 3);
    }

    /**
     * Returns the number of vertices (number of (x,y,z) values) of the array.
     * @return
    */
    int VertexArray::GetVertexCount() const {
        return mVertexCount;
    }
} // cg_engine