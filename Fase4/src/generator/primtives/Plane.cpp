//
// Created by Sandro Duarte on 10/03/2023.
//

#include <fstream>
#include <vector>

#include "primitives/Plane.h"
#include "Vec3f.h"
#include "utils/DumpVertices.h"




using std::vector;
using cg_math::Vec3f;

void Plane(int length, int divisions, const char *filePath) {
    vector<Vec3f> vertices;


    // calculates the size of each square of the plane
    float squareSize = static_cast<float>(length) / static_cast<float>(divisions);

    // finds the initial position of the plane (lower left corner)
    float x = static_cast<float>(-length) * 0.5f;
    // the y coordinate is always 0
    const float y = 0.0f;
    // finds the initial position of the plane (lower left corner)
    float z = static_cast<float>(-length) * 0.5f;

    // creates the plane by creating triangles and moving to the next square in the x-axis and z-axis (row by row)
    for (int i = 0; i < divisions; ++i) {
        for (int j = 0; j < divisions; ++j) {



            // finds the vertices of the lower triangle
            vertices.emplace_back(x, y, z);
            vertices.emplace_back(x, y, z + squareSize);
            vertices.emplace_back(x + squareSize, y, z + squareSize);

            // finds the vertices of the upper triangle
            vertices.emplace_back(x, y, z);
            vertices.emplace_back(x + squareSize, y, z + squareSize);
            vertices.emplace_back(x  + squareSize, y, z);

            // Moves to next upper left x coordinate of the square (next column)
            x += squareSize;
        }
        // Resets the x coordinate to the initial position of the row
        x -= static_cast<float>(length);
        // Moves to the next row (next line)
        z += squareSize;
    }

    DumpVertices(filePath, vertices.size(), vertices);
}
