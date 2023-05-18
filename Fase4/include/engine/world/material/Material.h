//
// Created by Sandro Duarte on 17/05/2023.
//

#ifndef ENGINE_MATERIAL_H
#define ENGINE_MATERIAL_H
#include "Vec3f.h"

class Material {
public:

    void SetProperties() const;

    void SetDiffuse(const cg_math::Vec3f& diffuse);
    void SetAmbient(const cg_math::Vec3f& ambient);
    void SetSpecular(const cg_math::Vec3f& specular);
    void SetEmission(const cg_math::Vec3f& emission);
    void SetShininess(float shininess);
private:
    float mDiffuse[3]{200,200,200};
    float mAmbient[3]{50,50,50};
    float mSpecular[3]{0,0,0};
    float mEmission[3]{0,0,0};
    float mShininess = 0;
};


#endif //ENGINE_MATERIAL_H
