#ifndef RendererOpenGL_H
#define RendererOpenGL_H

#include <QWidget>
#include <QOpenGLWidget>
#include <QOpenGLShaderProgram>
#include <QOpenGLFunctions>
#include <QOpenGLBuffer>
#include <QMatrix4x4>
#include <QMouseEvent>
#include <QOpenGLTexture>
#include <QTimer>

#include "Engine/Camera/camera.h"
#include "Engine/Objects/ObjectsLoader/OBJLoader.h"
#include "Engine/Objects/ObjectsManager/objmodel.h"

class RendererOpenGL : protected QOpenGLFunctions
{
public:
    QVector3D moveSpeed;
    QVector3D rotationSpeed;

private:
    QVector3D position;
    QVector3D rotation;
    QVector3D scale;

    QMatrix4x4 pMatrix;
    QMatrix4x4 transform;
    QOpenGLShaderProgram* shaderProgram;
    QOpenGLTexture *texture;
    QVector<QVector3D> verticesData;
    QVector<QVector3D> normalsData;
    QVector<QVector2D> textureCoordsData;
    QOpenGLBuffer graphicCardBuffer;

    int numberOfVerticles;
    float radius;

public:
    RendererOpenGL();
    ~RendererOpenGL();

    void init(QOpenGLShaderProgram* shader, OBJModel* model, QOpenGLTexture* texture);
    void update(int deltaTime);
    void draw(Camera camera, QMatrix4x4 pMatrix);

    QVector3D& getPosition()  {return position;}
    QVector3D& getRotation()  {return rotation;}
    QVector3D& getMoveSpeed()  {return moveSpeed;}
    QVector3D& getRotationSpeed()  {return rotationSpeed;}
    QMatrix4x4& getTransform()  { return transform; }

    float getRadius()  {return radius;}
    QVector3D getScale()  {return scale;}

    void setRadius(float value)  {radius = value;}
    void setScale(QVector3D value)  {scale = value;}
    void setScale(float x, float y, float z)  {scale.setX(x); scale.setY(y); scale.setZ(z);}
    void setPosition(QVector3D value)  {position = value;}
    void setPosition(float x, float y, float z)  {position.setX(x); position.setY(y); position.setZ(z);}
    void setRotation(QVector3D value)  {rotation = value;}
    void setRotation(float x, float y, float z)  {rotation.setX(x); rotation.setY(y); rotation.setZ(z);}


private:
    void getVerticlesData(OBJLoader data);
    void initializeGraphicBuffer();
    void assignTexture(QOpenGLTexture* texture);
};

#endif // RendererOpenGL_H
