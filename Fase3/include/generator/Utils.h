//
// Created by Sandro Duarte on 10/03/2023.
//

#ifndef ENGINE_UTILS_H
#define ENGINE_UTILS_H

#include <Vec3f.h>
#include <vector>

/**
 * @brief Saves the vertices to a file.
 * @details It saves the vertices to a file with the given path.
 * @param path The path to the file where the vertices will be saved.
 * @param nVertices The total number of vertices.
 * @param vertices The vertices to be saved.
 */
void DumpVertices(const char *path, unsigned int nVertices, std::vector<cg_math::Vec3f> &vertices);

#endif //ENGINE_UTILS_H
