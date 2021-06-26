#ifndef Simulator_H
#define Simulator_H

#define _USE_MATH_DEFINES

#include <QObject>
#include <QWidget>
#include <QOpenGLWidget>
#include <QOpenGLShaderProgram>
#include <QOpenGLFunctions>
#include <QOpenGLBuffer>
#include <QMatrix4x4>
#include <QDateTime>
#include <QKeyEvent>
#include <cmath>

#include "Engine/Objects/ObjectsManager/objmanager.h"
#include "Engine/Textures/texturesmanager.h"
#include "Engine/RendererOpenGL.h"
#include "Engine/Camera/camera.h"
#include "Plane.h"
#include "Input/InputKeyboard.h"

class Simulator : public QObject
{
    Q_OBJECT

private:
    QMatrix4x4 projectionMatrix;

    OBJManager objManager;
    TexturesManager texturesManager;
    Camera camera;
    Camera hudCamera;

    bool bModelview = false;
    InputKeyboard* inputKeyboard;

    Plane plane;

    RendererOpenGL skybox;
    RendererOpenGL sun;

    long int lastFrameTime; // im currently working on showing fps

public:
    Simulator();
    void initializeSimulator(QOpenGLShaderProgram* shader, InputKeyboard* inputKeyboard);
    void render();
    void update();

    void start();

    QMatrix4x4& getProjectionMatrixRef() noexcept {return projectionMatrix;}
    Camera& getCameraRef() noexcept {return camera;}
    float getPlaneAccelerate() noexcept {return plane.getAccelerate();}
    float getPlaneSpeed() noexcept { return plane.moveSpeed.length();}

private:
    void loadModels();
    void loadTextures();
    void createEnviroment(QOpenGLShaderProgram* shader);
    void createPlane(QOpenGLShaderProgram* shader);
    void input();

};

#endif // Simulator_H
