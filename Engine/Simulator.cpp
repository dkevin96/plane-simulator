#include "Simulator.h"

Simulator::Simulator()
{
    lastFrameTime = QDateTime::currentMSecsSinceEpoch();
}

void Simulator::initializeSimulator(QOpenGLShaderProgram* shader, InputKeyboard* inputKeyboard)
{
    this->inputKeyboard = inputKeyboard;

    loadModels();
    loadTextures();
    createEnviroment(shader);
    createPlane(shader);
}

void Simulator::render()
{
    skybox.draw(camera, projectionMatrix);

    sun.draw(camera, projectionMatrix);

    plane.draw(camera, projectionMatrix);
}

void Simulator::loadModels()
{
    QVector<QString> modelsToLoad;
    modelsToLoad.push_back(":/Objects/skybox");
    modelsToLoad.push_back(":/Objects/airplane");
    modelsToLoad.push_back(":/Objects/sun");
    objManager.loadAll(modelsToLoad);
}

void Simulator::loadTextures()
{
    QVector<QString> texturesToLoad;
    texturesToLoad.push_back(":/Textures/skybox");
    texturesToLoad.push_back(":/Textures/sun");
    texturesToLoad.push_back(":/Textures/toothless");
    texturesToLoad.push_back(":/Textures/forest");
    texturesToLoad.push_back(":/Textures/forest1");
    texturesToLoad.push_back(":/Textures/lostember1");
    texturesToLoad.push_back(":/Textures/lostember2");
    texturesToLoad.push_back(":/Textures/lostember3");
    texturesToLoad.push_back(":/Textures/lostember4");
    texturesToLoad.push_back(":/Textures/space1");
    texturesManager.loadAll(texturesToLoad);
}

void Simulator::createEnviroment(QOpenGLShaderProgram* shader)
{

    skybox.init(shader, objManager.getModel(":/Objects/skybox"), texturesManager.getTexture(":/Textures/lostember1"));
    skybox.setScale(100,100,100);
    skybox.setRotation(0,0,90);

    sun.setScale(200,200,200);
    sun.init(shader, objManager.getModel(":/Objects/sun"), texturesManager.getTexture(":/Textures/sun"));
    sun.getRotationSpeed().setX(0.5f);
    sun.setRotation(0,15,55);
    sun.setPosition(2000,7000,20000);

}

void Simulator::createPlane(QOpenGLShaderProgram* shader)
{
    plane.init(objManager.getModel(":/Objects/airplane"), texturesManager.getTexture(":/Textures/toothless"), shader);
}

void Simulator::input()
{


    if(inputKeyboard->isKeyPressed(Qt::Key::Key_W))
    {
        plane.rotation.setY(min(plane.rotation.y() + plane.agility, plane.maxturn));
    }
    if(inputKeyboard->isKeyPressed(Qt::Key::Key_S))
    {
        plane.rotation.setY(max(plane.rotation.y() - plane.agility, -plane.maxturn));
    }

    if(inputKeyboard->isKeyPressed(Qt::Key::Key_A))
    {
             plane.rotation.setX(min(plane.rotation.x() + plane.agility, plane.maxturn));

    }

    if (inputKeyboard->isKeyPressed(Qt::Key::Key_D))
    {
            plane.rotation.setX(max(plane.rotation.x() - plane.agility, -plane.maxturn));

    }


    if(inputKeyboard->isKeyPressed(Qt::Key::Key_Space))
    {
        plane.accelerate = min(plane.accelerate + plane.acceleration, plane.maxspeed);
    }

    if(inputKeyboard->isKeyPressed(Qt::Key::Key_F2))
    {
        plane.restoreStartPosition();
    }

    if(inputKeyboard->isKeyPressed(Qt::Key::Key_F3))
    {
        bModelview = true;
    }

    if(inputKeyboard->isKeyPressed(Qt::Key::Key_F4))
    {
        bModelview = false;
    }
}



void Simulator::start()
{
    lastFrameTime = QDateTime::currentMSecsSinceEpoch();
}

void Simulator::update()
{
    input();

    int deltaTime = QDateTime::currentMSecsSinceEpoch() - lastFrameTime;
    lastFrameTime = QDateTime::currentMSecsSinceEpoch();

    //skybox.setPosition(plane.getPosition());
    sun.update(deltaTime);

    plane.update(deltaTime);
    QVector3D testvec = QVector3D();

    //camera for plane
    if(bModelview == true)
    {
         camera.update(plane.getPosition() - plane.moveSpeed.normalized() * plane.accelerate * 50,testvec);
    }else{
    camera.update(plane.getPosition() - plane.moveSpeed.normalized() * plane.accelerate * 50 , plane.direction - plane.rotation * 2);
    }
}




