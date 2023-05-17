//
// Created by Sandro Duarte on 10/03/2023.
//

#include "primitives/Cone.h"
#include "Vec3f.h"
#include "utils/DumpModel.h"

using std::vector;
using cg_math::Vec3f;

void Cone(float radius, int height, int stacks, int slices, const char *fileName) {
    vector<Vec3f> vertices;
    vector<Vec3f> normals;
    vector<Vec3f> textureCoordinates;

    // The angle between each slice
    float alpha = static_cast<float>(2.0f * M_PI) / static_cast<float>(slices);

    // Filling vertices slice by slice
    for(int i = 0; i < slices; ++i) {

        // bottom triangle of the cone
        vertices.emplace_back(0,0,0);
        vertices.push_back(Vec3f::CreateCartesianFromPolar(i * alpha, 0, radius));
        vertices.push_back(Vec3f::CreateCartesianFromPolar((float)(i + 1) * alpha,0, radius));

        for(int j = 0; j < stacks; ++j) {

            // current height and radius of the current slice
            float currentHeight = ((float)height / (float)stacks) * j;
            float currentRadius = ((float)height - currentHeight) * radius / (float)height;

            // next height and radius of the current slice
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

    normals.reserve(vertices.size());
    for (auto &v: vertices) {
        normals.push_back(Vec3f::Normalize(v));
    }

    float xTexture = 0.0f;
    float yTexture = 0.0f;
    float delta = 1.0f / static_cast<float>(slices);

    for (int i = 0; i < slices; ++i) {
        textureCoordinates.emplace_back(0, 0,0);
        textureCoordinates.emplace_back(xTexture, yTexture + delta,0);
        textureCoordinates.emplace_back(xTexture + delta, yTexture + delta,0);

        for (int j = 0; j < stacks; ++j) {
            textureCoordinates.emplace_back(xTexture, yTexture + delta,0);
            textureCoordinates.emplace_back(xTexture + delta, yTexture + delta,0);
            textureCoordinates.emplace_back(xTexture, yTexture,0);

            textureCoordinates.emplace_back(xTexture, yTexture,0);
            textureCoordinates.emplace_back(xTexture + delta, yTexture + delta,0);
            textureCoordinates.emplace_back(xTexture + delta, yTexture,0);

             yTexture += delta;
        }
        xTexture += delta;
        yTexture = 0.0f;
    }

    DumpModel(fileName, vertices, normals, textureCoordinates);
}