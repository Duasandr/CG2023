//
// Created by Sandro Duarte on 10/03/2023.
//

#include <fstream>

#include "utils/DumpModel.h"

using std::ofstream;
using std::vector;
using cg_math::Vec3f;

void DumpModel(const char *path, std::vector<cg_math::Vec3f> &vertices, std::vector<cg_math::Vec3f> &normals,
                  std::vector<cg_math::Vec3f> &textureCoordinates) {
    std::ofstream ofs;

    ofs.open(path, std::ofstream::out | std::ofstream::trunc);

    // Write the number of vertices
    ofs << vertices.size() << '\n';
    // Write the vertices
    for (auto &vertex: vertices) {
        ofs << vertex << '\n';
    }

    ofs << normals.size() << '\n';
    for (auto &normal: normals) {
        ofs << normal << '\n';
    }

    ofs << textureCoordinates.size() << '\n';
    for (auto &textureCoordinate: textureCoordinates) {
        ofs << textureCoordinate.GetX() << ' ' << textureCoordinate.GetY() <<'\n';
    }

    ofs << std::endl;
    ofs.close();
}