//
// Created by Sandro Duarte on 10/03/2023.
//

#include <fstream>
#include <vector>

#include "primitives/Plane.h"
#include "Vec3f.h"
#include "utils/DumpModel.h"




using std::vector;
using cg_math::Vec3f;

void Plane(int length, int divisions, const char *filePath) {
    vector<Vec3f> vertices;
    vector<Vec3f> textureCoordinates;


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

    float xTexture = 0.0f;
    float yTexture = 1.0f;

    float delta = 1.0f / static_cast<float>(divisions);

    for (int i = 0; i < divisions; ++i) {
        for(int j = 0; j < divisions; ++j) {
           textureCoordinates.emplace_back(xTexture, yTexture,0);
           textureCoordinates.emplace_back(xTexture, yTexture - delta,0);
           textureCoordinates.emplace_back(xTexture + delta, yTexture - delta,0);

           textureCoordinates.emplace_back(xTexture, yTexture,0);
           textureCoordinates.emplace_back(xTexture + delta, yTexture - delta,0);
           textureCoordinates.emplace_back(xTexture + delta, yTexture,0);

           xTexture += delta;
        }
        xTexture = 0.0f;
        yTexture -= delta;
    }

    vector<Vec3f> normals(vertices.size(), Vec3f(0.0f, 1.0f, 0.0f));

    DumpModel(filePath, vertices, normals, textureCoordinates);
}
