//
// Created by Sandro Duarte on 24/04/2023.
//

#ifndef ENGINE_BEZIERPATCH_H
#define ENGINE_BEZIERPATCH_H


#include <cstdint>
#include <vector>
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
    BezierPatch();

    /**
     * @brief Destructor.
     * @ Frees allocated memory.
     */
    virtual ~BezierPatch();


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

    cg_math::Vec3f BezierPoint(uint32_t p, float u, float v);

    void Tessellate(const char *pathToFile);

private:
    /**
    * ////////////////////////////////
    * // Instance variables
    * ////////////////////////////////
    */

    uint32_t mTesselation;
    uint32_t mTotalIndices;
    uint32_t mTotalControlPoints;
    uint32_t *mIndices;
    cg_math::Vec3f * mControlPoints;
};


#endif //ENGINE_BEZIERPATCH_H
