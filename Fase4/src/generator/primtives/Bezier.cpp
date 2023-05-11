//
// Created by Sandro Duarte on 25/04/2023.
//

#include "primitives/Bezier.h"
#include "primitives/BezierPatch.h"

using std::cerr;
using std::endl;
using cg_math::Vec3f;
using std::vector;

void Bezier(const char* pathToPatchFile, unsigned int tesselation, const char *pathToOutputFile) {
    BezierPatch *patch = BezierPatch::Create(pathToPatchFile, tesselation);
    if(patch == nullptr) {
        cerr << "Error creating BezierPatch." << endl;
        return;
    }

    patch->Tessellate(pathToOutputFile);

    delete patch;
}