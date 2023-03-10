//
// Created by Sandro Duarte on 09/03/2023.
//

#ifndef ENGINE_VEC3F_H
#define ENGINE_VEC3F_H

namespace cg_math {

    /**
     * Represents a vector of three floats
     */
    class Vec3f {
    public:
        Vec3f();
        virtual ~Vec3f();

        /**
         * Sets x value.
         * @param x
         */
        void SetX(float x);

        /**
         * Sets y value.
         * @param y
         */
        void SetY(float y);

        /**
         * Sets z value.
         * @param z
         */
        void SetZ(float z);

        /**
         * Gets x value.
         * @return x
         */
        float GetX();

        /**
         * Gets y value.
         * @return
         */
        float GetY();

        /**
         * Gets z value.
         * @return
         */
        float GetZ();

    private:
        float mX;
        float mY;
        float mZ;
    };

} // cg_math

#endif //ENGINE_VEC3F_H
