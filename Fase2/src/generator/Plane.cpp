//
// Created by Sandro Duarte on 10/03/2023.
//

#include <fstream>
#include <vector>

#include <Plane.h>
#include <Vec3f.h>
#include <Utils.h>

using std::vector;
using cg_math::Vec3f;

void Plane(int length, int divisions, const char *filePath) {
    // Computes the total number of floats present in the vertices array
    vector<Vec3f> vertices;

    float squareSize = static_cast<float>(length) / static_cast<float>(divisions);

    // Starting from the left back edge
    float x = static_cast<float>(-length) * 0.5f;
    float y = 0.0f;
    float z = static_cast<float>(-length) * 0.5f;

    // fills with counterclockwise triangle vertices
    for (int i = 0; i < divisions; ++i) {
        for (int j = 0; j < divisions; ++j) {

            /**
            *  <---length--->
            * *--------------*
            * -  -           - ^
            * -   -    upper - |
            * -      -       - |
            * -        -     - length
            * -  lower   -   - |
            * -            - - |
            * *--------------* v   x ->
            * |
            * v
            * z
            */

            // finds the vertices of the lower triangle
            vertices.emplace_back(x, y, z);
            vertices.emplace_back(x, y, z + squareSize);
            vertices.emplace_back(x + squareSize, y, z + squareSize);

            // finds the vertices of the upper triangle
            vertices.emplace_back(x, y, z);
            vertices.emplace_back(x + squareSize, y, z + squareSize);
            vertices.emplace_back(x  + squareSize, y, z);

            // Moves to next upper left x
            x += squareSize;
        }
        // Moves back to the left side
        x -= static_cast<float>(length);
        // Moves a row down
        z += squareSize;
    }

    DumpVertices(filePath, vertices.size()*3, vertices);

}
