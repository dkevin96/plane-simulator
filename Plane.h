#ifndef Plane_H
#define Plane_H

#define _USE_MATH_DEFINES

#include <QVector>
#include <cmath>

#include "Engine/RendererOpenGL.h"
#include "Engine/Objects/ObjectsManager/objmanager.h"
#include "Engine/Textures/texturesmanager.h"

class Plane : public RendererOpenGL
{
public:
    float accelerate;
    float friction;
    float maxspeed;
    float acceleration;
    float agility;
    float maxturn;
    int currentTarget = 0;
    QVector3D direction;
    QVector3D rotation;

    bool bStopleft, bStopright;

public:
    Plane();

    void init(OBJModel* model, QOpenGLTexture* texture, QOpenGLShaderProgram* shader);
    void update(int deltaTime);
    void draw(Camera camera, QMatrix4x4 pMatrix);

    void setBoolLeft(bool mbool) {bStopleft = mbool;}
    void setBoolRight(bool mbool) {bStopright = mbool;}
public:
    float getAccelerate() {return accelerate;}
    void restoreStartPosition();
};

#endif
