//
// Created by Sandro Duarte on 24/04/2023.
//

#ifndef ENGINE_BEZIERPATCH_H
#define ENGINE_BEZIERPATCH_H


#include <cstdint>
#include <vector>
#include "Mat.h"
#include "Vec3f.h"

#define PATCH_SIZE 16

class BezierPatch {
public:
    /**
    * ////////////////////////////////
    * // Constructor and destructor
    * ////////////////////////////////
    */

    /**
     * @brief Empty constructor.
     */
    BezierPatch() = default;

    /**
     * @brief Destructor.
     * @ Frees allocated memory.
     */
    ~BezierPatch() = default;


    /**
    * ////////////////////////////////
    * // Static methods
    * ////////////////////////////////
    */

    /**
     * @brief Creates a BezierPatch from a file.
     * @param pathToFile
     * @param tesselation Number of segments the curves will have.
     * @return BezierPatch
     */
    static BezierPatch * Create(const char* pathToFile, uint32_t tesselation);


    void BezierPoint(uint32_t p, float u, float v);

    void Tessellate(const char *pathToFile);

private:
    /**
    * ////////////////////////////////
    * // Instance variables
    * ////////////////////////////////
    */

    /**
     * @brief Number of segments the curves will have.
     */
    uint32_t mTesselation;
    /**
     * @brief Pre-calculated Bezier patches.
     * @details Each patch is a is a vector of 3 4x4 matrices. One for each axis.
     */
    std::vector<std::vector<cg_math::Mat>> mPatches;
    std::vector<cg_math::Vec3f> mVertices;
    std::vector<cg_math::Vec3f> mNormals;
    std::vector<cg_math::Vec3f> mTextureCoordinates;
};


#endif //ENGINE_BEZIERPATCH_H
