//
// Created by Sandro Duarte on 10/03/2023.
//

#include <iostream>
#include <vector>
#include <Scene.h>

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
        Scene *scene = new Scene();

        scene->SetParams(pathToConfigXML);

        ResetCamera(scene);

        LoadModels(scene);

        return scene;
    }

    void Scene::LoadModels(Scene *scene) {
        for (auto &fileName: scene->mParams->GetModelFileNames()) {
            scene->LoadModel(fileName.c_str());
        }
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

    void Scene::LoadModel(const char *pathToFile) {
        Model *model = Model::LoadFromFile(pathToFile);

        if(model != nullptr){
            mModels.push_back(model);
        }else{
            std::cerr << "Error loading model from file: " << pathToFile << std::endl;
        }
    }

    int Scene::GetWindowHeight() const {
        return mParams->GetWindowHeight();
    }

    int Scene::GetWindowWidth() const {
        return mParams->GetWindowWidth();
    }

    const Camera &Scene::GetCamera() const {
        return mCamera;
    }

    const std::vector<Model *> &Scene::GetModels() const {
        return mModels;
    }
} // cg_engine