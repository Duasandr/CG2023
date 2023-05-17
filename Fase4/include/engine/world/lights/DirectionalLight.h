//
// Created by Sandro Duarte on 15/05/2023.
//

#ifndef ENGINE_DIRECTIONALLIGHT_H
#define ENGINE_DIRECTIONALLIGHT_H
#include "Light.h"

class DirectionalLight : public Light {
public:
    DirectionalLight() = default;
    DirectionalLight(float x, float y, float z);
    ~DirectionalLight()= default;

    void TurnOn() override;

private:
    float mDirection[4]{};
};


#endif //ENGINE_DIRECTIONALLIGHT_H
