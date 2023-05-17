//
// Created by Sandro Duarte on 10/03/2023.
//

#include "primitives/Sphere.h"
#include "Vec3f.h"
#include "utils/DumpModel.h"

using std::vector;
using cg_math::Vec3f;

void Sphere(float radius, int stacks, int slices, const char *fileName) {
    vector<Vec3f> vertices;
    vector<Vec3f> normals;
    vector<Vec3f> textureCoordinates;

    // The angle between each slice
    float alpha = static_cast<float>((2.0f * M_PI)) / static_cast<float>(slices);
    // The angle between each stack
    float beta = static_cast<float>(M_PI) / static_cast<float>(stacks);

    // Filling vertices of smaller circles each iteration
    for (int i = 0; i < slices; i++) {
        // stacks / 2 because we are going to draw the upper half and the lower half simultaneously
        for (int j = 0; j < stacks / 2; j++) {

            // Upper half
            vertices.push_back(Vec3f::CreateCartesianFromSphere(i * alpha, j * beta, radius));
            vertices.push_back(Vec3f::CreateCartesianFromSphere((i + 1) * alpha, j * beta, radius));
            vertices.push_back(Vec3f::CreateCartesianFromSphere(i * alpha, (j + 1) * beta, radius));


            vertices.push_back(Vec3f::CreateCartesianFromSphere((i + 1) * alpha, j * beta, radius));
            vertices.push_back(Vec3f::CreateCartesianFromSphere((i + 1) * alpha, (j + 1) * beta, radius));
            vertices.push_back(Vec3f::CreateCartesianFromSphere(i * alpha, (j + 1) * beta, radius));


            // Lower half
            vertices.push_back(Vec3f::CreateCartesianFromSphere(i * alpha, -j * beta, radius));
            vertices.push_back(Vec3f::CreateCartesianFromSphere(i * alpha, -(j + 1) * beta, radius));
            vertices.push_back(Vec3f::CreateCartesianFromSphere((i + 1) * alpha, -(j + 1) * beta, radius));

            vertices.push_back(Vec3f::CreateCartesianFromSphere((i + 1) * alpha, -(j + 1) * beta, radius));
            vertices.push_back(Vec3f::CreateCartesianFromSphere((i + 1) * alpha, -j * beta, radius));
            vertices.push_back(Vec3f::CreateCartesianFromSphere(i * alpha, -j * beta, radius));


        }
    }

    normals.reserve(vertices.size());
    for (auto &v: vertices) {
        normals.push_back(Vec3f::Normalize(v));
    }

    float xTexture = 0.0f;
    float yTexture = 0.5f;
    float delta = 1.0f / static_cast<float>(slices);

    for (int i = 0; i < slices; ++i) {
        for (int j = 0; j < stacks/2; ++j) {
            textureCoordinates.emplace_back(xTexture, yTexture, 0.0f);
            textureCoordinates.emplace_back(xTexture + delta, yTexture, 0.0f);
            textureCoordinates.emplace_back(xTexture, yTexture - delta, 0.0f);

            textureCoordinates.emplace_back(xTexture + delta, yTexture, 0.0f);
            textureCoordinates.emplace_back(xTexture + delta, yTexture - delta, 0.0f);
            textureCoordinates.emplace_back(xTexture, yTexture - delta, 0.0f);

            textureCoordinates.emplace_back(xTexture, yTexture, 0.0f);
            textureCoordinates.emplace_back(xTexture, yTexture - delta, 0.0f);
            textureCoordinates.emplace_back(xTexture + delta, yTexture - delta, 0.0f);

            textureCoordinates.emplace_back(xTexture + delta, yTexture - delta, 0.0f);
            textureCoordinates.emplace_back(xTexture + delta, yTexture, 0.0f);
            textureCoordinates.emplace_back(xTexture, yTexture, 0.0f);

            yTexture -= delta;
        }
        yTexture = 0.5f;
        xTexture += delta;
    }


    DumpModel(fileName, vertices, normals, textureCoordinates);
}