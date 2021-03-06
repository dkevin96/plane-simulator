#pragma once
#include <string>
#include <vector>
#include <fstream>
#include <QVector2D>
#include <QVector3D>
#include <QVector>
#include <QFile>
#include <QTextStream>

#include "Engine/Objects/ObjectsLoader/Vertex.h"

using namespace std;

class OBJLoader
{
private:
    QVector<QVector3D> verticesData;
    QVector<QVector3D> normalsData;
    QVector<QVector2D> textureCoordsData;
    QVector<Vertex> vertexData;

public:
    OBJLoader();
    ~OBJLoader();

    bool LoadFromFile(QString fileName);

    QVector<QVector3D> getVerticesData()  {return verticesData;}
    QVector<QVector3D> getNormalsData()  {return normalsData;}
    QVector<QVector2D> getTextureCoordsData()  {return textureCoordsData;}
    QVector<Vertex> getVertexData()  {return vertexData;}

    bool isNormalsLoaded()  {return normalsData.size() == 0 ? false : true;}
    bool isTexCoordsLoaded()  {return textureCoordsData.size() == 0 ? false : true;}

private:
    bool parse(QString content);
    bool parseVertices(QString line);
    bool parseTextureCoordinates(QString line);
    bool parseNormals(QString line);
    bool parseFaces(QString line);
};
