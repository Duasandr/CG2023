//
// Created by Sandro Duarte on 09/03/2023.
//

#ifndef ENGINE_SCENEPARAM_H
#define ENGINE_SCENEPARAM_H

namespace cg_engine {

    class SceneParam {
    public:
        SceneParam();
        virtual ~SceneParam();

        static SceneParam * Init(const char* pathToConfigXml);

        void Destroy();

    private:
        static void ParseWindow(SceneParam *params, const tinyxml2::XMLElement *window);

        static void ParseCameraPosition(SceneParam *params, const tinyxml2::XMLElement *position);

        static void ParseCameraLookAt(SceneParam *params, const tinyxml2::XMLElement *lookAt);

        static void ParseCameraUp(SceneParam *params, const tinyxml2::XMLElement *up);

        static void ParseCameraProjection(SceneParam *params, const tinyxml2::XMLElement *projection);

        static float ParseFloat(const char *str);

        static void SetFloat(const char *str, float &value);

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

        std::vector<std::string> *mModelFileNames;


        static void ParseFileNames(SceneParam *params, tinyxml2::XMLElement *models);
    };

} // cg_engine

#endif //ENGINE_SCENEPARAM_H
