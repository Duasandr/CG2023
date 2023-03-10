//
// Created by Sandro Duarte on 10/03/2023.
//

#ifndef ENGINE_MODEL_H
#define ENGINE_MODEL_H
#include <fstream>
#include <cstdint>

namespace cg_engine {

    class Model {
    public:
        Model();
        virtual ~Model();

        static Model *LoadFromFile(const char *path);

        void Destroy();

    private:
        void SetVertex(std::ifstream &ifs);

        uint64_t mBytes;
        unsigned int mVertexCount;
        float *mVertex;
    };

} // cg_engine

#endif //ENGINE_MODEL_H
