//
// Created by Sandro Duarte on 10/03/2023.
//

#ifndef ENGINE_SCENE_H
#define ENGINE_SCENE_H
#include <SceneParam.h>
#include <Camera.h>

namespace cg_engine {
    using cg_math::Vec3f;

    class Scene {
    public:
        Scene();
        virtual ~Scene();

        void SetParams(const char *pathToConfigXML);

        void Destroy();
    private:
        SceneParam *mParams;
        Camera mCamera;
    };

} // cg_engine

#endif //ENGINE_SCENE_H
