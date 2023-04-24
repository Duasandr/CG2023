//
// Created by Sandro Duarte on 09/03/2023.
//
#include <iostream>

#include <Primitives.h>
#include <Parser.h>

using std::cerr;
using std::endl;

int main(int argc, char **argv) {
    using cg_utils::Parser;

    // Check if the number of arguments is valid for the primitive
    if (argc < 2) {
        std::cerr << "Invalid number of arguments" << std::endl;
        return -1;
    }

    // Get the primitive name from the first argument
    std::string primitive = argv[1];

    // Check if the primitive is valid

    if (primitive == "plane") {
        int length = Parser::ParseInt(argv[2]);
        int divisions = Parser::ParseInt(argv[3]);

        Plane(length, divisions, argv[4]);

        return 0;
    }

    if (primitive == "box") {
        int length = Parser::ParseInt(argv[2]);
        int divisions = Parser::ParseInt(argv[3]);

        Box(length, divisions, argv[4]);

        return 0;
    }

    if(primitive == "sphere")  {
        float r = Parser::ParseFloat(argv[2]);
        int slices = Parser::ParseInt(argv[3]);
        int stacks = Parser::ParseInt(argv[4]);

        Sphere(r, stacks, slices, argv[5]);

        return 0;
    }

    if(primitive == "cone")  {
        float radius = Parser::ParseFloat(argv[2]);
        int height = Parser::ParseInt(argv[3]);
        int slices = Parser::ParseInt(argv[4]);
        int stacks = Parser::ParseInt(argv[5]);

        Cone(radius, height, stacks, slices, argv[6]);

        return 0;
    }

    // If the primitive is not valid, print an error message
    cerr << "Invalid primitive: " << primitive << endl;

    return 1;
}