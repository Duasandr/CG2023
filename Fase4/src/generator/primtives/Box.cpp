//
// Created by Sandro Duarte on 10/03/2023.
//

#include <vector>

#include "primitives/Box.h"
#include "Vec3f.h"
#include "utils/DumpModel.h"

// TODO: Improve the code to be more generic and reusable. It is not a good idea to have a function for each face. Change the plane to reuse the same function for each face.


using std::vector;
using cg_math::Vec3f;

void UpperFace(int length, int divisions, vector<Vec3f> &vertices, vector<Vec3f> &normals ,vector<Vec3f> &textureCoordinates) {
    float squareSize = static_cast<float>(length) / static_cast<float>(divisions);

    // Starting from the left back edge
    float x = static_cast<float>(-length) * 0.5f;
    float y = static_cast<float>(length) * 0.5f;
    float z = static_cast<float>(-length) * 0.5f;

    // fills with counterclockwise triangle vertices
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

            // Moves to next upper left x
            x += squareSize;
        }
        // Moves back to the left side
        x -= static_cast<float>(length);
        // Moves a row down
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
    int size = divisions * divisions;
    for (int i = 0; i < size; ++i) {
        normals.emplace_back(0.0f, 1.0f, 0.0f);
    }
}

void LowerFace(int length, int divisions, vector<Vec3f> &vertices,  vector<Vec3f> &normals ,vector<Vec3f> &textureCoordinates) {
    float squareSize = static_cast<float>(length) / static_cast<float>(divisions);

    // Starting from the left back edge
    float x = static_cast<float>(-length) * 0.5f;
    float y = static_cast<float>(-length) * 0.5f;
    float z = static_cast<float>(-length) * 0.5f;

    // fills with clockwise triangle vertices
    for (int i = 0; i < divisions; ++i) {
        for (int j = 0; j < divisions; ++j) {

            // finds the vertices of the lower triangle
            vertices.emplace_back(x + squareSize, y, z + squareSize);
            vertices.emplace_back(x, y, z + squareSize);
            vertices.emplace_back(x, y, z);

            // finds the vertices of the upper triangle
            vertices.emplace_back(x  + squareSize, y, z);
            vertices.emplace_back(x + squareSize, y, z + squareSize);
            vertices.emplace_back(x, y, z);

            // Moves to next upper left x
            x += squareSize;
        }
        // Moves back to the left side
        x -= static_cast<float>(length);
        // Moves a row down
        z += squareSize;
    }
    float xTexture = 0.0f;
    float yTexture = 1.0f;

    float delta = 1.0f / static_cast<float>(divisions);

    for (int i = 0; i < divisions; ++i) {
        for(int j = 0; j < divisions; ++j) {
            textureCoordinates.emplace_back(xTexture + delta, yTexture - delta,0);
            textureCoordinates.emplace_back(xTexture, yTexture - delta,0);
            textureCoordinates.emplace_back(xTexture, yTexture,0);

            textureCoordinates.emplace_back(xTexture + delta, yTexture,0);
            textureCoordinates.emplace_back(xTexture + delta, yTexture - delta,0);
            textureCoordinates.emplace_back(xTexture, yTexture,0);

            xTexture += delta;
        }
        xTexture = 0.0f;
        yTexture -= delta;
    }
    int size = divisions * divisions;
    for (int i = 0; i < size; ++i) {
        normals.emplace_back(0.0f, -1.0f, 0.0f);
    }
}

void LeftFace(int length, int divisions, vector<Vec3f> &vertices,  vector<Vec3f> &normals ,vector<Vec3f> &textureCoordinates) {
    float squareSize = static_cast<float>(length) / static_cast<float>(divisions);

    // Starting from the left back edge
    float x = static_cast<float>(-length) * 0.5f;
    float y = static_cast<float>(length) * 0.5f;
    float z = static_cast<float>(-length) * 0.5f;

    // fills with clockwise triangle vertices
    for (int i = 0; i < divisions; ++i) {
        for (int j = 0; j < divisions; ++j) {

            // finds the vertices of the lower triangle
            vertices.emplace_back(x, y - squareSize, z + squareSize);
            vertices.emplace_back(x, y, z + squareSize);
            vertices.emplace_back(x, y, z);

            // finds the vertices of the upper triangle
            vertices.emplace_back(x, y - squareSize, z);
            vertices.emplace_back(x, y - squareSize, z + squareSize);
            vertices.emplace_back(x, y, z);

            // Moves to next upper left x
            z += squareSize;
        }
        // Moves back to the left side
        z -= static_cast<float>(length);
        // Moves a row down
        y -= squareSize;
    }
    float xTexture = 0.0f;
    float yTexture = 1.0f;

    float delta = 1.0f / static_cast<float>(divisions);

    for (int i = 0; i < divisions; ++i) {
        for(int j = 0; j < divisions; ++j) {
            textureCoordinates.emplace_back(xTexture + delta, yTexture - delta,0);
            textureCoordinates.emplace_back(xTexture, yTexture - delta,0);
            textureCoordinates.emplace_back(xTexture, yTexture,0);

            textureCoordinates.emplace_back(xTexture + delta, yTexture,0);
            textureCoordinates.emplace_back(xTexture + delta, yTexture - delta,0);
            textureCoordinates.emplace_back(xTexture, yTexture,0);

            xTexture += delta;
        }
        xTexture = 0.0f;
        yTexture -= delta;
    }
    int size = divisions * divisions;
    for (int i = 0; i < size; ++i) {
        normals.emplace_back(-1.0f, 0.0f, 0.0f);
    }
}

void RightFace(int length, int divisions, vector<Vec3f> &vertices,  vector<Vec3f> &normals ,vector<Vec3f> &textureCoordinates) {
    float squareSize = static_cast<float>(length) / static_cast<float>(divisions);

    // Starting from the left back edge
    float x = static_cast<float>(length) * 0.5f;
    float y = static_cast<float>(length) * 0.5f;
    float z = static_cast<float>(-length) * 0.5f;

    // fills with counterclockwise triangle vertices
    for (int i = 0; i < divisions; ++i) {
        for (int j = 0; j < divisions; ++j) {

            // finds the vertices of the lower triangle
            vertices.emplace_back(x, y, z);
            vertices.emplace_back(x, y, z + squareSize);
            vertices.emplace_back(x, y - squareSize, z + squareSize);

            // finds the vertices of the upper triangle
            vertices.emplace_back(x, y, z);
            vertices.emplace_back(x, y - squareSize, z + squareSize);
            vertices.emplace_back(x, y - squareSize, z);

            // Moves to next upper left x
            z += squareSize;
        }
        // Moves back to the left side
        z -= static_cast<float>(length);
        // Moves a row down
        y -= squareSize;
    }
    float xTexture = 0.0f;
    float yTexture = 1.0f;

    float delta = 1.0f / static_cast<float>(divisions);

    for (int i = 0; i < divisions; ++i) {
        for(int j = 0; j < divisions; ++j) {
            textureCoordinates.emplace_back(xTexture + delta, yTexture - delta,0);
            textureCoordinates.emplace_back(xTexture, yTexture - delta,0);
            textureCoordinates.emplace_back(xTexture, yTexture,0);

            textureCoordinates.emplace_back(xTexture + delta, yTexture,0);
            textureCoordinates.emplace_back(xTexture + delta, yTexture - delta,0);
            textureCoordinates.emplace_back(xTexture, yTexture,0);

            xTexture += delta;
        }
        xTexture = 0.0f;
        yTexture -= delta;
    }
    int size = divisions * divisions;
    for (int i = 0; i < size; ++i) {
        normals.emplace_back(1.0f, 0.0f, 0.0f);
    }
}

void BackFace(int length, int divisions, vector<Vec3f> &vertices,  vector<Vec3f> &normals ,vector<Vec3f> &textureCoordinates) {
    float squareSize = static_cast<float>(length) / static_cast<float>(divisions);

    // Starting from the left back edge
    float x = static_cast<float>(-length) * 0.5f;
    float y = static_cast<float>(length) * 0.5f;
    float z = static_cast<float>(-length) * 0.5f;

    // fills with counterclockwise triangle vertices
    for (int i = 0; i < divisions; ++i) {
        for (int j = 0; j < divisions; ++j) {

            // finds the vertices of the lower triangle
            vertices.emplace_back(x, y, z);
            vertices.emplace_back(x + squareSize, y, z);
            vertices.emplace_back(x + squareSize, y - squareSize, z);

            // finds the vertices of the upper triangle
            vertices.emplace_back(x, y, z);
            vertices.emplace_back(x + squareSize, y - squareSize, z);
            vertices.emplace_back(x, y - squareSize, z);

            // Moves to next upper left x
            x += squareSize;
        }
        // Moves back to the left side
        x -= static_cast<float>(length);
        // Moves a row down
        y -= squareSize;
    }
    float xTexture = 0.0f;
    float yTexture = 1.0f;

    float delta = 1.0f / static_cast<float>(divisions);

    for (int i = 0; i < divisions; ++i) {
        for(int j = 0; j < divisions; ++j) {
            textureCoordinates.emplace_back(xTexture + delta, yTexture - delta,0);
            textureCoordinates.emplace_back(xTexture, yTexture - delta,0);
            textureCoordinates.emplace_back(xTexture, yTexture,0);

            textureCoordinates.emplace_back(xTexture + delta, yTexture,0);
            textureCoordinates.emplace_back(xTexture + delta, yTexture - delta,0);
            textureCoordinates.emplace_back(xTexture, yTexture,0);

            xTexture += delta;
        }
        xTexture = 0.0f;
        yTexture -= delta;
    }
    int size = divisions * divisions;
    for (int i = 0; i < size; ++i) {
        normals.emplace_back(0.0f, 0.0f, -1.0f);
    }
}

void FrontFace(int length, int divisions, vector<Vec3f> &vertices,  vector<Vec3f> &normals ,vector<Vec3f> &textureCoordinates) {
    float squareSize = static_cast<float>(length) / static_cast<float>(divisions);

    // Starting from the left back edge
    float x = static_cast<float>(-length) * 0.5f;
    float y = static_cast<float>(length) * 0.5f;
    float z = static_cast<float>(length) * 0.5f;

    // fills with counterclockwise triangle vertices
    for (int i = 0; i < divisions; ++i) {
        for (int j = 0; j < divisions; ++j) {

            // finds the vertices of the lower triangle
            vertices.emplace_back(x + squareSize, y - squareSize, z);
            vertices.emplace_back(x + squareSize, y, z);
            vertices.emplace_back(x, y, z);

            // finds the vertices of the upper triangle
            vertices.emplace_back(x, y - squareSize, z);
            vertices.emplace_back(x + squareSize, y - squareSize, z);
            vertices.emplace_back(x, y, z);

            // Moves to next upper left x
            x += squareSize;
        }
        // Moves back to the left side
        x -= static_cast<float>(length);
        // Moves a row down
        y -= squareSize;
    }
    float xTexture = 0.0f;
    float yTexture = 1.0f;

    float delta = 1.0f / static_cast<float>(divisions);

    for (int i = 0; i < divisions; ++i) {
        for(int j = 0; j < divisions; ++j) {
            textureCoordinates.emplace_back(xTexture + delta, yTexture - delta,0);
            textureCoordinates.emplace_back(xTexture, yTexture - delta,0);
            textureCoordinates.emplace_back(xTexture, yTexture,0);

            textureCoordinates.emplace_back(xTexture + delta, yTexture,0);
            textureCoordinates.emplace_back(xTexture + delta, yTexture - delta,0);
            textureCoordinates.emplace_back(xTexture, yTexture,0);

            xTexture += delta;
        }
        xTexture = 0.0f;
        yTexture -= delta;
    }
    int size = divisions * divisions;
    for (int i = 0; i < size; ++i) {
        normals.emplace_back(0.0f, 0.0f, 1.0f);
    }
}

void Box(int length, int divisions, const char *filePath) {
    vector<Vec3f> vertices;
    vector<Vec3f> normals;
    vector<Vec3f> textureCoordinates;

    // upper face
    UpperFace(length,divisions,vertices, normals, textureCoordinates);
    // lower face
    LowerFace(length,divisions,vertices, normals, textureCoordinates);
    // left face
    LeftFace(length,divisions,vertices, normals, textureCoordinates);
    // right face
    RightFace(length,divisions,vertices, normals, textureCoordinates);
    // front face
    FrontFace(length,divisions,vertices, normals, textureCoordinates);
    // back face
    BackFace(length,divisions,vertices, normals, textureCoordinates);


    DumpModel(filePath,vertices, normals, textureCoordinates);
}
