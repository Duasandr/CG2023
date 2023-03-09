//
// Created by Sandro Duarte on 09/03/2023.
//

#ifndef ENGINE_SCENEPARAM_H
#define ENGINE_SCENEPARAM_H
#include <string>

namespace cg_engine {

    class SceneParam {
    public:
        SceneParam();
        virtual ~SceneParam();

        static SceneParam * Init(const char* pathToConfigXml);

        void Destroy();

    private:
        float mWindowWidth;
        float mWindowHeight;
        float mCameraPosX;
        float mCameraPosY;
        float mCameraPosZ;
        float mCameraLookAtX;
        float mCameraLookAtY;
        float mCameraLookAtZ;
        float mCameraUpX;
        float mCameraUpY;
        float mCameraUpZ;
        float mCameraFOV;
        float mCameraFar;
        float mCameraNear;

        unsigned int mModelCount;
        std::string *mModelFileNames;
    };

} // cg_engine

#endif //ENGINE_SCENEPARAM_H
