//
// Created by Sandro Duarte on 09/03/2023.
//
#include <iostream>

#include "primitives/Primitives.h"
#include "primitives/Bezier.h"
#include "CommonParser.h"
#define MODEL_PATH "models/"

using std::cerr;
using std::endl;

int main(int argc, char **argv) {
    using cg_utils::CommonParser;

    // Check if the number of arguments is valid for the primitive
    if (argc < 2) {
        std::cerr << "Invalid number of arguments" << std::endl;
        return -1;
    }
    std::string path(MODEL_PATH);
    path += argv[argc - 1];

    // Get the primitive name from the first argument
    std::string primitive = argv[1];

    // Check if the primitive is valid

    if (primitive == "plane") {
        int length = CommonParser::ParseInt(argv[2]);
        int divisions = CommonParser::ParseInt(argv[3]);

        Plane(length, divisions, path.c_str());

        return 0;
    }

    if (primitive == "box") {
        int length = CommonParser::ParseInt(argv[2]);
        int divisions = CommonParser::ParseInt(argv[3]);

        Box(length, divisions, path.c_str());

        return 0;
    }

    if(primitive == "sphere")  {
        float r = CommonParser::ParseFloat(argv[2]);
        int slices = CommonParser::ParseInt(argv[3]);
        int stacks = CommonParser::ParseInt(argv[4]);

        Sphere(r, stacks, slices, path.c_str());

        return 0;
    }

    if(primitive == "cone")  {
        float radius = CommonParser::ParseFloat(argv[2]);
        int height = CommonParser::ParseInt(argv[3]);
        int slices = CommonParser::ParseInt(argv[4]);
        int stacks = CommonParser::ParseInt(argv[5]);

        Cone(radius, height, stacks, slices, path.c_str());

        return 0;
    }

    if(primitive == "bezier")  {
        Bezier(argv[2], CommonParser::ParseInt(argv[3]), path.c_str());
        return 0;
    }

    // If the primitive is not valid, print an error message
    cerr << "Invalid primitive: " << primitive << endl;

    return 1;
}