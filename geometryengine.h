#ifndef GEOMETRYENGINE_H
#define GEOMETRYENGINE_H

#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>
#include "VertexCalc.h"


//ͼ�λ��Ƽ�������
class GeometryEngine : protected QOpenGLFunctions
{
public:
    GeometryEngine();
    virtual ~GeometryEngine();

	void setAttribute(QOpenGLShaderProgram *program, VertexCalc *vertexCalc);
	void drawVertexCalc(QOpenGLShaderProgram *program, VertexCalc *vertexCalc);
private:
    QOpenGLBuffer arrayBuf;
    QOpenGLBuffer indexBuf;
};

#endif // GEOMETRYENGINE_H
