//
// Created by Sandro Duarte on 10/03/2023.
//

#include "Sphere.h"
#include "Vec3f.h"
#include "Utils.h"

using std::vector;
using cg_math::Vec3f;

void Sphere(float radius, int stacks, int slices, const char *fileName) {
    vector<Vec3f> vertices;

    float alpha = static_cast<float>((2.0f * M_PI)) / static_cast<float>(slices);
    float beta = static_cast<float>(M_PI) / static_cast<float>(stacks);

    for (int i = 0; i < slices; i++)
    {
        for (int j = 0; j < stacks / 2; j++)
        {

            // Upper half

            vertices.push_back(Vec3f::CreateCartesianFromSphere(i * alpha, j * beta, radius));
            vertices.push_back(Vec3f::CreateCartesianFromSphere((i+1) * alpha,j * beta, radius));
            vertices.push_back(Vec3f::CreateCartesianFromSphere(i * alpha, (j + 1) * beta, radius));

            vertices.push_back(Vec3f::CreateCartesianFromSphere((i+1) * alpha,j * beta, radius));
            vertices.push_back(Vec3f::CreateCartesianFromSphere((i+1) * alpha,(j + 1) * beta, radius));
            vertices.push_back(Vec3f::CreateCartesianFromSphere(i * alpha, (j + 1) * beta, radius));


            // Lower half
            vertices.push_back(Vec3f::CreateCartesianFromSphere(i * alpha, -j * beta, radius));
            vertices.push_back(Vec3f::CreateCartesianFromSphere(i * alpha, -(j + 1) * beta, radius));
            vertices.push_back(Vec3f::CreateCartesianFromSphere((i+1) * alpha,-(j + 1) * beta, radius));

            vertices.push_back(Vec3f::CreateCartesianFromSphere((i+1) * alpha,-(j + 1) * beta, radius));
            vertices.push_back(Vec3f::CreateCartesianFromSphere((i+1) * alpha, -j * beta, radius));
            vertices.push_back(Vec3f::CreateCartesianFromSphere(i * alpha, -j * beta, radius));

        }
    }


    DumpVertices(fileName, vertices.size() * 3,vertices);
}