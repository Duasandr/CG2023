//
// Created by Sandro Duarte on 10/03/2023.
//
#include <iostream>
#include "Model.h"

namespace cg_engine {
    using std::ifstream;

    Model::Model() {
        mSize = 0;
        mVertex = nullptr;
    }

    Model::~Model() {
        Destroy();
    }

    void Model::Destroy() {
        delete mVertex;
    }

    Model *Model::LoadFromFile(const char *path) {
        ifstream ifs;
        Model *res = new Model();

        ifs.open(path);

        if (ifs.fail()) {
            std::cerr << "Error opening file : " << path << std::endl;
            return nullptr;
        }

        res->SetVertex(ifs);
        ifs.close();

        return res;
    }

    void Model::SetVertex(ifstream &ifs) {
        ifs >> mSize;

        mVertex = new float[mSize];

        for (int i = 0; i < mSize; ++i) {
            ifs >> mVertex[i];
        }
    }

    unsigned int Model::GetVertexCount() const {
        return mSize;
    }

    const float *Model::GetVertices() const {
        return mVertex;
    }
} // cg_engine