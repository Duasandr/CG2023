//
// Created by Sandro Duarte on 10/03/2023.
//

#ifndef GENERATOR_DUMP_VERTICES_H
#define GENERATOR_DUMP_VERTICES_H

#include "Vec3f.h"
#include <vector>

/**
 * @brief Saves the vertices to a file.
 * @details It saves the vertices to a file with the given path.
 * @param path The path to the file where the vertices will be saved.
 * @param nVertices The total number of vertices.
 * @param vertices The vertices to be saved.
 */
void DumpModel(const char *path, std::vector<cg_math::Vec3f> &vertices, std::vector<cg_math::Vec3f> &normals,
                  std::vector<cg_math::Vec3f> &textureCoordinates);

#endif //GENERATOR_DUMP_VERTICES_H
