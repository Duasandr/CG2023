//
// Created by Sandro Duarte on 15/05/2023.
//

#include "world/lights/Light.h"

// 0x4000 is the first light id because it doesn't conflict with the default OpenGL lights.
int Light::LIGHT_ID = 0x4000;

int Light::GenerateLightId() {
    return LIGHT_ID++;
}
