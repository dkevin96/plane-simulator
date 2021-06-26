#include "Plane.h"


Plane::Plane()
{
    accelerate = 0;
    maxspeed = 0.15;
    acceleration = 0.01;
    friction = 1.01;
    direction = QVector3D(0,0,0);
    agility = 0.2;
    maxturn = 10;
    rotation = QVector3D(0,0,0);

    setScale(0.3f, 0.3f, 0.3f);

    setPosition(0,15,1700);
}

void Plane::init(OBJModel* model, QOpenGLTexture* texture, QOpenGLShaderProgram* shader)
{
    RendererOpenGL::init(shader, model, texture);
}

void Plane::update(int deltaTime)
{

    direction.setX(direction.x() + rotation.x());
    direction.setY(direction.y() + rotation.y());
    direction.setZ(direction.z() + rotation.z());

    // rotation must be set after each update
    rotation = rotation/1.1;
    accelerate = max(accelerate / 1.01 - 0.005, 0.0);

    QMatrix4x4 rotationmatrix = QMatrix4x4();

    //this help the plane can fly up or down when you change the direction
    rotationmatrix.rotate(direction.x(), 1, 0, 0);
    rotationmatrix.rotate(direction.y(), 0, 1, 0);


    QVector3D movement = rotationmatrix.mapVector(QVector3D(0,0,accelerate));

    moveSpeed = (moveSpeed / friction) + movement;

    getRotation().setX(direction.x());
    getRotation().setY(direction.y());
    getRotation().setZ(direction.z());

    RendererOpenGL::update(deltaTime);
}

void Plane::draw(Camera camera, QMatrix4x4 pMatrix)
{
    RendererOpenGL::draw(camera,pMatrix);
}

void Plane::restoreStartPosition()
{

    //Restore start position and rotation
    setPosition(0,15,1700);
    setRotation(0.0,0.0,0.0);


    //Restore start speed
    direction = QVector3D(0,0,0);
    rotation = QVector3D(0,0,0);
    moveSpeed = QVector3D(0,0,0);
    rotationSpeed = QVector3D(0,0,0);

    bStopleft = false;
    bStopright = false;
}


