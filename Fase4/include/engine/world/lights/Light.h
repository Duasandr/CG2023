//
// Created by Sandro Duarte on 15/05/2023.
//

#ifndef ENGINE_LIGHT_H
#define ENGINE_LIGHT_H


class Light {
public:
    Light() { mId = GenerateLightId(); }
    virtual void TurnOn() = 0;
    static int GenerateLightId();

    int GetId() const { return mId; }

protected:
    static int LIGHT_ID;

    int mId;
};




#endif //ENGINE_LIGHT_H
