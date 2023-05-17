//
// Created by Sandro Duarte on 15/05/2023.
//

#include "world/lights/Light.h"

int Light::LIGHT_ID = 0x4000;

int Light::GenerateLightId() {
    return LIGHT_ID++;
}
