//
// Created by Sandro Duarte on 10/03/2023.
//

#include "Cone.h"
#include "Vec3f.h"
#include "Utils.h"

using std::vector;
using cg_math::Vec3f;

void Cone(float radius, int height, int stacks, int slices, const char *fileName) {
    std::vector<Vec3f> vertices;

    float alpha = static_cast<float>(2.0f * M_PI) / static_cast<float>(slices);

    // filling vertices of smaller circles each iteration
    for(int i = 0; i < slices; ++i) {
        // base triangles
        vertices.emplace_back(0,0,0);
        vertices.push_back(Vec3f::CreateCartesianFromPolar(i * alpha, 0, radius));
        vertices.push_back(Vec3f::CreateCartesianFromPolar((float)(i + 1) * alpha,0, radius));



        for(int j = 0; j < stacks; ++j) {

            float currentHeight = ((float)height / (float)stacks) * j;
            float currentRadius = ((float)height - currentHeight) * radius / (float)height;
            float nextHeight = ((float)height / (float)stacks) * (float)(j + 1);
            float nextRadius = ((float)height - nextHeight) * radius / (float)height;


            // upper triangle
            vertices.push_back(Vec3f::CreateCartesianFromPolar(i * alpha , nextHeight, nextRadius));
            vertices.push_back(Vec3f::CreateCartesianFromPolar((float)(i + 1) * alpha, nextHeight, nextRadius));
            vertices.push_back(Vec3f::CreateCartesianFromPolar((float)i * alpha, currentHeight, currentRadius));


            // lower triangle
            vertices.push_back(Vec3f::CreateCartesianFromPolar(i * alpha , currentHeight, currentRadius));
            vertices.push_back(Vec3f::CreateCartesianFromPolar((i + 1) * alpha , nextHeight, nextRadius));
            vertices.push_back(Vec3f::CreateCartesianFromPolar((i + 1) * alpha , currentHeight, currentRadius));
        }
    }

    DumpVertices(fileName, vertices.size() * 3 ,vertices);
}