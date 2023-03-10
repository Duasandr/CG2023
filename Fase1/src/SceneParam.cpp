//
// Created by Sandro Duarte on 09/03/2023.
//
#include <iostream>
#include <string>
#include <vector>

#include <tinyxml2.h>
#include <SceneParam.h>


using std::cout;
using std::cerr;
using std::endl;
using std::string;
using std::vector;

using tinyxml2::XMLDocument;
using tinyxml2::XMLNode;
using tinyxml2::XMLElement;

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

        mModelFileNames = new vector<string>();
    }

    SceneParam::~SceneParam() {
        Destroy();
    }

    /**
     * Initializes SceneParams with a configuration XML file.
     * @param pathToConfigXml
     * @return SceneParams or nullptr if unsuccessful
     */
    SceneParam *SceneParam::Init(const char *pathToConfigXml) {
        SceneParam *params = new SceneParam();
        XMLDocument configFile;

        int res = configFile.LoadFile(pathToConfigXml);

        if(res != tinyxml2::XML_SUCCESS) {
            cerr << "Error opening XML configuration file." << endl;
            return nullptr;
        }

        XMLElement *world = configFile.FirstChildElement("world");

        XMLElement *window = world->FirstChildElement("window");

        XMLElement *camera = world->FirstChildElement("camera");
        XMLElement *position = camera->FirstChildElement("position");
        XMLElement *lookAt = camera->FirstChildElement("lookAt");
        XMLElement *up = camera->FirstChildElement("up");
        XMLElement *projection = camera->FirstChildElement("projection");

        XMLElement *groups = world->FirstChildElement("group");
        XMLElement *models = groups->FirstChildElement("models");

        ParseWindow(params, window);

        ParseCameraPosition(params, position);

        ParseCameraLookAt(params, lookAt);

        ParseCameraUp(params, up);

        ParseCameraProjection(params, projection);

        ParseFileNames(params, models);

        return params;
    }

    void SceneParam::ParseFileNames(SceneParam *params, XMLElement *models) {
        for (XMLElement *model = models->FirstChildElement("model"); model != nullptr; model = models->NextSiblingElement("model")) {
            params->mModelFileNames->push_back(model->Attribute("file"));
        }
    }

    void SceneParam::ParseCameraProjection(SceneParam *params, const XMLElement *projection) {
        SetFloat(projection->Attribute("fov"), params->mCameraFOV);
        SetFloat(projection->Attribute("near"), params->mCameraNear);
        SetFloat(projection->Attribute("far"), params->mCameraFar);
    }

    void SceneParam::ParseCameraUp(SceneParam *params, const XMLElement *up) {
        SetFloat(up->Attribute("x"), params->mCameraUpX);
        SetFloat(up->Attribute("y"), params->mCameraUpY);
        SetFloat(up->Attribute("z"), params->mCameraUpZ);
    }

    void SceneParam::ParseCameraLookAt(SceneParam *params, const XMLElement *lookAt) {
        SetFloat(lookAt->Attribute("x"), params->mCameraLookAtX);
        SetFloat(lookAt->Attribute("y"), params->mCameraLookAtY);
        SetFloat(lookAt->Attribute("z"), params->mCameraLookAtZ);
    }

    void SceneParam::ParseCameraPosition(SceneParam *params, const XMLElement *position) {
        SetFloat(position->Attribute("x"), params->mCameraPosX);
        SetFloat(position->Attribute("y"), params->mCameraPosY);
        SetFloat(position->Attribute("z"), params->mCameraPosZ);
    }

    void SceneParam::ParseWindow(SceneParam *params, const XMLElement *window) {
        SetFloat(window->Attribute("width"), params->mWindowWidth);
        SetFloat(window->Attribute("height"), params->mWindowHeight);
    }

    /**
     * Releases allocated memory of Scene.
     */
    void SceneParam::Destroy() {
        delete mModelFileNames;
    }

    /**
     * Parses a given string to float.
     * @param str
     * @return float
     * @throws std:.domain_error when invalid string is present
     */
    float SceneParam::ParseFloat(const char *str) {
        float res = 0.0f;
        char *rest;

        res = static_cast<float>(strtof(str, &rest));

        if(*rest != '\0') {
            throw std::domain_error(str);
        }

        return res;
    }

    /**
     * Utility function to set float values. Checks for parsing errors.
     * @param str
     * @param value field to modify
     */
    void SceneParam::SetFloat(const char *str, float &value) {
        try {
            value = ParseFloat(str);
        }
        catch (std::domain_error &e) {
            cerr << "Error parsing float. " << e.what() << endl;
            value = 0;
        }
    }

    float SceneParam::GetWindowWidth() const {
        return mWindowWidth;
    }

    float SceneParam::GetWindowHeight() const {
        return mWindowHeight;
    }

    float SceneParam::GetCameraPosX() const {
        return mCameraPosX;
    }

    float SceneParam::GetCameraPosY() const {
        return mCameraPosY;
    }

    float SceneParam::GetCameraPosZ() const {
        return mCameraPosZ;
    }

    float SceneParam::GetCameraLookAtX() const {
        return mCameraLookAtX;
    }

    float SceneParam::GetCameraLookAtY() const {
        return mCameraLookAtY;
    }

    float SceneParam::GetCameraLookAtZ() const {
        return mCameraLookAtZ;
    }

    float SceneParam::GetCameraUpX() const {
        return mCameraUpX;
    }

    float SceneParam::GetCameraUpY() const {
        return mCameraUpY;
    }

    float SceneParam::GetCameraUpZ() const {
        return mCameraUpZ;
    }

    float SceneParam::GetCameraFOV() const {
        return mCameraFOV;
    }

    float SceneParam::GetCameraFar() const {
        return mCameraNear;
    }

    float SceneParam::GetCameraNear() const {
        return mCameraFar;
    }

    std::vector<std::string> &SceneParam::GetModelFileNames() const {
        return *mModelFileNames;
    }

    std::ostream &operator<<(std::ostream &os, const SceneParam &params) {
        os << "Window Width: " << params.GetWindowWidth() << '\n';
        os << "Window Height: " << params.GetWindowHeight() << '\n';

        os << "Camera Position X: " << params.GetCameraPosX() << '\n';
        os << "Camera Position Y: " << params.GetCameraPosY() << '\n';
        os << "Camera Position Z: " << params.GetCameraPosZ() << '\n';

        os << "Camera Look At X: " << params.GetCameraLookAtX() << '\n';
        os << "Camera Look At Y: " << params.GetCameraLookAtY() << '\n';
        os << "Camera Look At Z: " << params.GetCameraLookAtZ() << '\n';

        os << "Camera Up X: " << params.GetCameraUpX() << '\n';
        os << "Camera Up Y: " << params.GetCameraUpY() << '\n';
        os << "Camera Up Z: " << params.GetCameraUpZ() << '\n';

        os << "Camera FOV: " << params.GetCameraFOV() << '\n';
        os << "Camera Near: " << params.GetCameraNear() << '\n';
        os << "Camera Far: " << params.GetCameraFar() << '\n';

        for(auto &fileName: params.GetModelFileNames()) {
            os << "Model File: " << fileName << '\n';
        }

        os << endl;

        return os;
    }
} // cg_engine