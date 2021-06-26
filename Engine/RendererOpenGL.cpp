#include "RendererOpenGL.h"

RendererOpenGL::RendererOpenGL() : texture(0)
{
    position = QVector3D(0.0,0.0,0.0);
    rotation = QVector3D(0.0,0.0,0.0);
    scale = QVector3D(1, 1, 1);

    moveSpeed = QVector3D(0.0,0.0,0.0);
    rotationSpeed = QVector3D(0.0,0.0,0.0);
    texture = nullptr;
    numberOfVerticles = 0;

}

RendererOpenGL::~RendererOpenGL()
{

}

void RendererOpenGL::getVerticlesData(OBJLoader data)
{
    int vertexsCount = data.getVertexData().size();

    Vertex vertex;
    QVector3D v1;
    QVector3D v2;
    QVector3D v3;

    for(int i=0; i<vertexsCount; i++)
    {
        vertex = data.getVertexData().at(i);

        v1 = data.getVerticesData().at(vertex.vertices.x() - 1);
        v2 = data.getVerticesData().at(vertex.vertices.y() - 1);
        v3 = data.getVerticesData().at(vertex.vertices.z() - 1);

        verticesData.push_back(v1);
        verticesData.push_back(v2);
        verticesData.push_back(v3);

        if(data.isTexCoordsLoaded() == false)
        {
            textureCoordsData.push_back(QVector2D(0.0,1.0));
            textureCoordsData.push_back(QVector2D(1.0,1.0));
            textureCoordsData.push_back(QVector2D(1.0,0.0));
        }
        else
        {
            textureCoordsData.push_back(data.getTextureCoordsData().at(vertex.textures.x() - 1));
            textureCoordsData.push_back(data.getTextureCoordsData().at(vertex.textures.y() - 1));
            textureCoordsData.push_back(data.getTextureCoordsData().at(vertex.textures.z() - 1));
        }
    }
}


void RendererOpenGL::initializeGraphicBuffer()
{
    graphicCardBuffer.create();
    graphicCardBuffer.bind();
    graphicCardBuffer.allocate(numberOfVerticles * (3 + 2) * sizeof(GLfloat));

    int offset = 0;
    graphicCardBuffer.write(offset, verticesData.constData(), numberOfVerticles * 3 * sizeof(GLfloat));
    offset += numberOfVerticles * 3 * sizeof(GLfloat);

    graphicCardBuffer.write(offset, textureCoordsData.constData(), numberOfVerticles * 2 * sizeof(GLfloat));

    graphicCardBuffer.release();
}

void RendererOpenGL::assignTexture(QOpenGLTexture* texture)
{
    this->texture = texture;
    this->texture->setMinificationFilter(QOpenGLTexture::Nearest);
    this->texture->setMagnificationFilter(QOpenGLTexture::Linear);
}

void RendererOpenGL::init(QOpenGLShaderProgram* shader, OBJModel* model, QOpenGLTexture* texture)
{
    initializeOpenGLFunctions();

    shaderProgram = shader;
    OBJLoader data = model->getData();
    getVerticlesData(data);
    numberOfVerticles = verticesData.count();
    initializeGraphicBuffer();
    assignTexture(texture);
}

void RendererOpenGL::update(int deltaTime)
{
    // speed of plane
    position += (moveSpeed * ((float)deltaTime / 16.0));
    // rotation of sun
    rotation += (rotationSpeed * ((float)deltaTime / 16.0));
}

void RendererOpenGL::draw(Camera camera, QMatrix4x4 pMatrix)
{
    QMatrix4x4 vMatrix = camera.GetMatrix();

    transform = QMatrix4x4();
    transform.translate(position.x(), position.y(), position.z());
    transform.rotate(rotation.x(), 1, 0, 0);
    transform.rotate(rotation.y(), 0, 1, 0);
    transform.rotate(rotation.z(), 0, 0, 1);
    transform.scale(scale);

    QMatrix4x4 mvMatrix = vMatrix * transform;


    shaderProgram->bind();
    texture->bind();

    shaderProgram->setUniformValue("mvpMatrix", pMatrix * mvMatrix);

    shaderProgram->setUniformValue("texture", 0);

    graphicCardBuffer.bind();
    int offset = 0;
    shaderProgram->setAttributeBuffer("vertex", GL_FLOAT, offset, 3, 0);
    shaderProgram->enableAttributeArray("vertex");
    offset += numberOfVerticles * 3 * sizeof(GLfloat);

    shaderProgram->setAttributeBuffer("textureCoordinate", GL_FLOAT, offset, 2, 0);
    shaderProgram->enableAttributeArray("textureCoordinate");
    graphicCardBuffer.release();

    glDrawArrays(GL_TRIANGLES, 0, numberOfVerticles);

    shaderProgram->disableAttributeArray("vertex");

    shaderProgram->disableAttributeArray("textureCoordinate");

    shaderProgram->release();
    texture->release();
}
