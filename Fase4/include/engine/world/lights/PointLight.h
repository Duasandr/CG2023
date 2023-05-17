//
// Created by Sandro Duarte on 15/05/2023.
//

#ifndef ENGINE_POINTLIGHT_H
#define ENGINE_POINTLIGHT_H

#include "Light.h"

class PointLight : public Light{
public:
    PointLight(float x, float y, float z);
    ~PointLight() = default;

    void TurnOn() override;
private:
    float mPosition[4]{};
};


#endif //ENGINE_POINTLIGHT_H
