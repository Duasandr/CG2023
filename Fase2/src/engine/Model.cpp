//
// Created by Sandro Duarte on 10/03/2023.
//
#ifdef __APPLE__
#include <glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif
#include <iostream>
#include "Model.h"

namespace cg_engine {
    using std::ifstream;
    using std::exception;
    using std::cerr;
    using std::endl;

    /**
     * Constructs a Model object from a .3d file.
     * @param pathToFile
     * @throws std::exception when file not found
    */
    Model::Model(const char *pathToFile) {
        mVertexArray.SetVertices(pathToFile);
        mVertexArray.CopyData(mVertexBuffer);
    }

    /**
     * Creates a model from a .3d file
     * @param path
     * @return Model object or nullptr when fail
    */
    Model *Model::Create(const char *pathToFile) {
        Model *res = nullptr;

        try {
            res = new Model(pathToFile);
        }
        catch(exception &e) {
            cerr << "File not found: " << pathToFile << endl;

            delete res;

            return nullptr;
        }

        return res;
    }

    void Model::Draw() const {
        mVertexBuffer.Bind();
        glVertexPointer(3, GL_FLOAT, 0, 0);
        glDrawArrays(GL_TRIANGLES, 0, mVertexArray.GetVertexCount());
    }
} // cg_engine