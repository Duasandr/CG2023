//
// Created by Sandro Duarte on 10/03/2023.
//
#include <iostream>
#include <Model.h>

namespace cg_engine {
    using std::ifstream;

    Model::Model() {
        mBytes = 0;
        mVertexCount = 0;
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

        try {
            ifs.open(path);
            res->SetVertex(ifs);
            ifs.close();
        }
        catch (std::exception &e) {
            std::cerr << e.what() << std::endl;
            res = nullptr;
        }

        return res;
    }

    void Model::SetVertex(ifstream &ifs) {
        ifs >> mVertexCount;
        mBytes = mVertexCount * sizeof(float);
        mVertex = new float[mVertexCount];

        for (int i = 0; i < mVertexCount; ++i) {
            ifs >> mVertex[i];
        }
    }
} // cg_engine