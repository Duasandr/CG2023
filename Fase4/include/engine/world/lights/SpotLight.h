//
// Created by Sandro Duarte on 15/05/2023.
//

#ifndef ENGINE_SPOTLIGHT_H
#define ENGINE_SPOTLIGHT_H
#include "Light.h"

class SpotLight : public Light {
public:
    SpotLight() = default;
    SpotLight(float px, float py, float pz, float dx, float dy, float dz, float cutOff);
    ~SpotLight()= default;

    void TurnOn() override;

private:
    float mPosition[4]{};
    float mDirection[4]{};
    float mCutOff;

};


#endif //ENGINE_SPOTLIGHT_H
