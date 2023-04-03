//
// Created by Sandro Duarte on 03/04/2023.
//

#include "world/camera/CameraType.h"

namespace cg_engine {
    void CameraType::Move(Camera &camera, const unsigned char option) {
        // The camera moves in the direction of the camera's local axes.
        switch (option) {
            case 'w':
                // The camera moves in the direction of the camera's local z-axis.
                MoveForward(camera);
                break;//
            case 's':
                MoveBackward(camera);
                break;
            case 'a':
                // The camera moves in the direction of the camera's local x-axis.
                MoveLeft(camera);
                break;
            case 'd':
                MoveRight(camera);
                break;
            case 'q':
                // The camera moves in the direction of the camera's local y-axis.
                MoveUp(camera);
                break;
            case 'e':
                MoveDown(camera);
                break;
            default:
                break;
        }
    }
} // cg_engine