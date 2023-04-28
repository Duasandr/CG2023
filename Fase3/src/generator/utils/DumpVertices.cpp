//
// Created by Sandro Duarte on 10/03/2023.
//

#include <fstream>

#include "utils/DumpVertices.h"

using std::ofstream;
using std::vector;
using cg_math::Vec3f;

void DumpVertices(const char *path, const unsigned int nVertices, vector<Vec3f> &vertices) {
    std::ofstream ofs;

    ofs.open(path);

    // Write the number of vertices
    ofs << nVertices << '\n';
    // Write the vertices
    for (auto &vertex: vertices) {
        ofs << vertex << '\n';
    }

    ofs << std::endl;
    ofs.close();
}