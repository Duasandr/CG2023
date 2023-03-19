//
// Created by Sandro Duarte on 10/03/2023.
//

#ifndef ENGINE_UTILS_H
#define ENGINE_UTILS_H

#include <Vec3f.h>
#include <vector>

void DumpVertices(const char *path, unsigned int totalValues, std::vector<cg_math::Vec3f> &vertices);

#endif //ENGINE_UTILS_H
