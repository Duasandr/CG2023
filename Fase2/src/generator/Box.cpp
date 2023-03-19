//
// Created by Sandro Duarte on 10/03/2023.
//

#include <fstream>
#include <vector>

#include <Box.h>
#include <Vec3f.h>
#include <Utils.h>

using std::vector;
using cg_math::Vec3f;

void UpperFace(int length, int divisions, vector<Vec3f> &vertices) {
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
}

void LowerFace(int length, int divisions, vector<Vec3f> &vertices) {
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
}

void LeftFace(int length, int divisions, vector<Vec3f> &vertices) {
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
}

void RightFace(int length, int divisions, vector<Vec3f> &vertices) {
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
}

void BackFace(int length, int divisions, vector<Vec3f> &vertices) {
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
}

void FrontFace(int length, int divisions, vector<Vec3f> &vertices) {
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
}

void Box(int length, int divisions, const char *filePath) {
    vector<Vec3f> vertices;

    // upper face
    UpperFace(length,divisions,vertices);
    // lower face
    LowerFace(length,divisions,vertices);
    // left face
    LeftFace(length,divisions,vertices);
    // right face
    RightFace(length,divisions,vertices);
    // front face
    FrontFace(length,divisions,vertices);
    // back face
    BackFace(length,divisions,vertices);

    DumpVertices(filePath, vertices.size(),vertices);

}
