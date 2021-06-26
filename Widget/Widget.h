#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QOpenGLWidget>
#include <QOpenGLShaderProgram>
#include <QOpenGLFunctions>
#include <QOpenGLBuffer>
#include <QMouseEvent>
#include <QOpenGLTexture>
#include <QTimer>
#include <QTime>
#include <QLabel>
#include <QPushButton>
#include <QGridLayout>
#include <QProgressBar>
#include <QApplication>
#include <QDesktopWidget>

#include "Engine/Simulator.h"
#include "Input/InputKeyboard.h"



class Widget : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT

private:
    //Shader progrem
    QOpenGLShaderProgram shaderProgram;

    //Game timers to render enviroment and update layout
    QTimer Timer;

    //Game specific objects
    Simulator Simulator;
    InputKeyboard inputKeyboard;

    QPoint mousePos;

    QString cssLabels;
    QString cssButtons;
    QLabel *fpsCounterLabel;

public:
    Widget(QWidget *parent = 0);
    ~Widget();
    QSize sizeHint() const;

public slots:
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);

protected:
    void initializeGL();
    void resizeGL(int width, int height);
    void paintGL();

    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

private:
    void loadShaders();
    void makeConnection();
    void createLayout();
    void initializeTimers();


};

#endif // WIDGET_H
