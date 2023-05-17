//
// Created by Sandro Duarte on 17/05/2023.
//
#ifdef __APPLE__

#include <glut.h>

#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif
#include "world/color/Color.h"

void Color::Paint() const {
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT,mAmbient);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mSpecular);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mDiffuse);
    glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, mEmission);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, mShininess);
}

void Color::SetDiffuse(const cg_math::Vec3f& diffuse) {
    mDiffuse[0] = diffuse.GetX();
    mDiffuse[1] = diffuse.GetY();
    mDiffuse[2] = diffuse.GetZ();
}

void Color::SetAmbient(const cg_math::Vec3f& ambient) {
    mAmbient[0] = ambient.GetX();
    mAmbient[1] = ambient.GetY();
    mAmbient[2] = ambient.GetZ();
}

void Color::SetSpecular(const cg_math::Vec3f& specular) {
    mSpecular[0] = specular.GetX();
    mSpecular[1] = specular.GetY();
    mSpecular[2] = specular.GetZ();
}

void Color::SetEmission(const cg_math::Vec3f& emission) {
    mEmission[0] = emission.GetX();
    mEmission[1] = emission.GetY();
    mEmission[2] = emission.GetZ();
}

void Color::SetShininess(float shininess) {
    mShininess = shininess;
}
