#include "Widget.h"

Widget::Widget(QWidget *parent) : QOpenGLWidget(parent)
{
    connect(&Timer, SIGNAL(timeout()), this, SLOT(update()));
}

Widget::~Widget()
{
}

QSize Widget::sizeHint() const
{
    return QSize(640, 480);
}

void Widget::loadShaders()
{
    shaderProgram.addShaderFromSourceFile(QOpenGLShader::Vertex, ":/Shaders/LightningVertexShader");
    shaderProgram.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/Shaders/LightningFragmentShader");
    shaderProgram.link();
}

void Widget::initializeGL()
{
    initializeOpenGLFunctions();
    glEnable(GL_DEPTH_TEST); //Show the object near the camera
    glClearColor(1,1,1,1); //Set Background Color

    loadShaders();
    Simulator.initializeSimulator(&shaderProgram, &inputKeyboard);
}

void Widget::resizeGL(int width, int height)
{
    if (height == 0)
    {
        height = 1; //Apspect = width / height , height can not be 0
    }

    Simulator.getProjectionMatrixRef().setToIdentity();
    Simulator.getProjectionMatrixRef().perspective(60.0, (float) width / (float) height, 1, 500000.0f);
    glViewport(0, 0, width, height);
    Simulator.start();
    Timer.start(16);

}

void Widget::paintGL()
{
    Simulator.update();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    Simulator.render();
}

void Widget::mousePressEvent(QMouseEvent *event)
{
    mousePos = event->pos();
    event->accept();
}

void Widget::mouseMoveEvent(QMouseEvent *event)
{
    Simulator.getCameraRef().addToDirection((event->pos().x() - mousePos.x())/2, (event->pos().y() - mousePos.y())/2, 0);
    mousePos = event->pos();
    event->accept();
}

void Widget::mouseReleaseEvent(QMouseEvent *event)
{
    event->accept();
}

void Widget::keyPressEvent(QKeyEvent *event)
{

    Qt::Key key = (Qt::Key)event->key();

    inputKeyboard.keyPressed(key);

}

void Widget::keyReleaseEvent(QKeyEvent *event)
{
    Qt::Key key = (Qt::Key)event->key();

    inputKeyboard.keyReleased(key);

}


