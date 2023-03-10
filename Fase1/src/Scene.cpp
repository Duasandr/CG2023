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
} // cg_engine