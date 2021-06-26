QT += core gui multimediawidgets

 QT += widgets

TEMPLATE = app


SOURCES += main.cpp \
    Engine/Camera/camera.cpp \
    Engine/Objects/ObjectsLoader/OBJLoader.cpp \
    Engine/Objects/ObjectsManager/objmanager.cpp \
    Engine/Objects/ObjectsManager/objmodel.cpp \
    Engine/RendererOpenGL.cpp \
    Engine/Simulator.cpp \
    Engine/Textures/texturedata.cpp \
    Engine/Textures/texturesmanager.cpp \
    Input/InputKeyboard.cpp \
    Plane.cpp \
    Widget/Widget.cpp \

HEADERS  +=   \
    Engine/Camera/camera.h \
    Engine/Objects/ObjectsLoader/OBJLoader.h \
    Engine/Objects/ObjectsLoader/Vertex.h \
    Engine/Objects/ObjectsManager/objmanager.h \
    Engine/Objects/ObjectsManager/objmodel.h \
    Engine/RendererOpenGL.h \
    Engine/Simulator.h \
    Engine/Textures/texturedata.h \
    Engine/Textures/texturesmanager.h \
    Input/InputKeyboard.h \
    Plane.h \
    Widget/Widget.h \

RESOURCES += \
    resources.qrc


