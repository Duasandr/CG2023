//
// Created by Sandro Duarte on 10/03/2023.
//

#include <Scene.h>
#include <iostream>
namespace cg_engine {
    using cg_engine::SceneParam;

    Scene::Scene() {
        mParams = nullptr;
        mCamera = Camera();
    }

    Scene::~Scene() {
        Destroy();
    }

    void Scene::SetParams(const char *pathToConfigXML) {
        mParams = SceneParam::Init(pathToConfigXML);

#ifndef NDEBUG
        std::cout << "---- Scene -> SetParams() ----" << '\n';
        std::cout << *mParams;
        std::cout << "---- END ----" << std::endl;
#endif
    }

    void Scene::Destroy() {
        delete mParams;
    }

    Scene *Scene::Init(const char *pathToConfigXML) {
        Scene *res = new Scene();

        res->SetParams(pathToConfigXML);

        ResetCamera(res);

        for (auto &fileName: res->mParams->GetModelFileNames()) {
            
        }

        return res;
    }

    void Scene::ResetCamera(Scene *scene) {
        if(scene->mParams != nullptr) {
            scene->mCamera.SetPosition(scene->mParams->GetCameraPosX(), scene->mParams->GetCameraPosY(),
                                       scene->mParams->GetCameraPosZ());
            scene->mCamera.SetLookAt(scene->mParams->GetCameraLookAtX(), scene->mParams->GetCameraLookAtY(),
                                     scene->mParams->GetCameraLookAtZ());
            scene->mCamera.SetUp(scene->mParams->GetCameraUpX(), scene->mParams->GetCameraUpY(),
                                 scene->mParams->GetCameraUpZ());
            scene->mCamera.SetProjection(scene->mParams->GetCameraFOV(), scene->mParams->GetCameraNear(),
                                         scene->mParams->GetCameraFar());
        }
    }
} // cg_engine