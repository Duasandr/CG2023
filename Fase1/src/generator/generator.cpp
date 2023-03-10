//
// Created by Sandro Duarte on 09/03/2023.
//
#include <iostream>

#include <Primitives.h>

using std::cerr;
using std::endl;

int main(int argc, char **argv) {
    if (argc < 2) {
        std::cerr << "Invalid number of arguments" << std::endl;
        return -1;
    }

    std::string primitive = argv[1];

    if (primitive == "plane") {
        char *rest;
        int length = static_cast<int>(strtol(argv[2], &rest, 10));
        int divisions = static_cast<int>(strtol(argv[3], &rest, 10));

        if (*rest != '\0') {
            cerr << "Error parsing plane." << endl;
        }

        Plane(length, divisions, argv[4]);

        return 0;
    }
}