//
// Created by Sandro Duarte on 10/03/2023.
//

#include <fstream>

#include <Utils.h>

using std::ofstream;
using std::vector;
using cg_math::Vec3f;

void DumpVertices(const char *path, const unsigned int totalValues, vector<Vec3f> &vertices) {
    std::ofstream ofs;

    ofs.open(path);

    ofs << totalValues << '\n';
    for (auto &vertex: vertices) {
        ofs << vertex << '\n';
    }

    ofs << std::endl;
    ofs.close();
}