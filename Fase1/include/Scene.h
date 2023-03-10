//
// Created by Sandro Duarte on 10/03/2023.
//

#ifndef ENGINE_SCENE_H
#define ENGINE_SCENE_H
#include <vector>
#include <SceneParam.h>
#include <Camera.h>
#include <Model.h>

namespace cg_engine {
    using cg_math::Vec3f;

    class Scene {
    public:
        Scene();
        virtual ~Scene();

        static Scene *Init(const char *pathToConfigXML);

        void SetParams(const char *pathToConfigXML);

        void LoadModel(const char *pathToFile);

        void Destroy();
    private:
        SceneParam *mParams;
        Camera mCamera;
        std::vector<Model*> mModels;

        static void ResetCamera(Scene *scene);

        static void LoadModels(Scene *scene);
    };

} // cg_engine

#endif //ENGINE_SCENE_H
