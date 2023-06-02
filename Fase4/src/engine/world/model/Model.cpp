//
// Created by Sandro Duarte on 10/03/2023.
//
#ifdef __APPLE__

#include <glut.h>

#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif

#include <IL/il.h>
#include <iostream>
#include "world/model/Model.h"
#define MODEL_PATH "models/"
#define TEXTURE_PATH "textures/"

namespace cg_engine {
    using std::ifstream;
    using std::exception;
    using std::cerr;
    using std::endl;

    Model::Model(const char *pathToFile) {
        setArrays(pathToFile);
    }

    /**
     * Constructs a Model object from a .3d file.
     * @param pathToFile
     * @throws std::exception when file not found
    */
    Model::Model(const char *pathToFile, const char *texturePath) {
        setArrays(pathToFile);
        mTextureId = LoadTexture(texturePath);
    }

    Model *Model::Create(const char *path) {
        Model *res;
        std::string pathTofile(MODEL_PATH);
        pathTofile += std::string(path);

        try {
            res = new Model(pathTofile.c_str());
        }
        catch (exception &e) {
            cerr << "File not found: " << path << endl;
            delete res;
            return nullptr;
        }
        return res;
    }

    /**
     * Creates a model from a .3d file
     * @param path
     * @return Model object or nullptr when fail
    */
    Model *Model::Create(const char *pathToFile, const char *texturePath) {
        Model *res = nullptr;

        std::string path(MODEL_PATH);
        std::string texture(TEXTURE_PATH);

        path += std::string(pathToFile);
        texture += std::string(texturePath);

        try {
            res = new Model(path.c_str(), texture.c_str());
        }
        catch (exception &e) {
            cerr << "File not found: " << pathToFile << endl;

            delete res;

            return nullptr;
        }

        return res;
    }

    /**
     * @brief Draws the model
     * @details Draws the model using the vertex buffer
     */
    void Model::Draw() const {


        mVertexBuffer.Bind();
        glVertexPointer(3, GL_FLOAT, 0, 0);

        mNormalBuffer.Bind();
        glNormalPointer(GL_FLOAT, 0, 0);

        if (mTextureId > 0) {
            glEnable(GL_TEXTURE_2D);

            // bind the texture
            glBindTexture(GL_TEXTURE_2D, mTextureId);

            mTextureBuffer.Bind();
            glTexCoordPointer(2, GL_FLOAT, 0, 0);
        }

        mMaterial->SetProperties();

        glDrawArrays(GL_TRIANGLES, 0, mPositionArray.GetVertexCount());

        if (mTextureId > 0) {
            glBindTexture(GL_TEXTURE_2D, 0);
            glDisable(GL_TEXTURE_2D);
        }
    }

    void Model::setArrays(const char *pathToFile) {
        ifstream ifs;
        ifs.open(pathToFile, ifstream::in);

        if (!ifs.is_open()) {
            throw exception();
        }

        mPositionArray.SetVertices(ifs);
        mPositionArray.CopyData(mVertexBuffer);

        mNormalArray.SetVertices(ifs);
        mNormalArray.CopyData(mNormalBuffer);

        mTextureArray.SetVertices(ifs);
        mTextureArray.CopyData(mTextureBuffer);

        ifs.close();
    }

    unsigned int Model::LoadTexture(const char *path) {

        unsigned int t, tw, th;
        unsigned char *texData;
        unsigned int texID;
// Iniciar o DevIL
        ilInit();
// Colocar a origem da textura no canto inferior esquerdo
        ilEnable(IL_ORIGIN_SET);
        ilOriginFunc(IL_ORIGIN_LOWER_LEFT);
// Carregar a textura para memória
        ilGenImages(1, &t);
        ilBindImage(t);
        ilLoadImage((ILstring) path);
        tw = ilGetInteger(IL_IMAGE_WIDTH);
        th = ilGetInteger(IL_IMAGE_HEIGHT);
// Assegurar que a textura se encontra em RGBA (Red, Green, Blue, Alpha)
        ilConvertImage(IL_RGBA, IL_UNSIGNED_BYTE);
        texData = ilGetData();
// Gerar a textura para a placa gráfica
        glGenTextures(1, &texID);
        glBindTexture(GL_TEXTURE_2D, texID);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
// Upload dos dados de imagem

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, tw, th, 0, GL_RGBA, GL_UNSIGNED_BYTE, texData);
        glGenerateMipmap(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, 0);

        return texID;
    }

    Model::Model() {
        mTextureId = -1;
    }

    void Model::SetColor(Material *color) {
        delete mMaterial;
        mMaterial = color;
    }

} // cg_engine