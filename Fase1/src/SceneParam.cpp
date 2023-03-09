//
// Created by Sandro Duarte on 09/03/2023.
//
#include <iostream>
#include <string>
#include "SceneParam.h"

using std::cout;
using std::endl;
using std::string;

namespace cg_engine {
    SceneParam::SceneParam() {
        mWindowWidth = 0.0f;
        mWindowHeight = 0.0f;
        mCameraPosX = 0.0f;
        mCameraPosY = 0.0f;
        mCameraPosZ = 0.0f;
        mCameraLookAtX = 0.0f;
        mCameraLookAtY = 0.0f;
        mCameraLookAtZ = 0.0f;
        mCameraUpX = 0.0f;
        mCameraUpY = 0.0f;
        mCameraUpZ = 0.0f;
        mCameraFOV = 0.0f;
        mCameraFar = 0.0f;
        mCameraNear = 0.0f;

        mModelCount = 0;
        mModelFileNames = nullptr;
    }

    SceneParam::~SceneParam() {
    }

    SceneParam *SceneParam::Init(const char *pathToConfigXml) {
        return nullptr;
    }

    void SceneParam::Destroy() {
        delete mModelFileNames;
    }
} // cg_engine