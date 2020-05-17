#ifndef VERTEXCALC_H
#define VERTEXCALC_H

#include "Config.h"
#include <stdlib.h>
#include <string>
#include <QVector3D>
#include <QVector4D>

//目前有三种有效模型类型
typedef enum{
	FOR_LINES = 1,		//顶点信息（三维坐标+四维颜色坐标），索引信息（成对的顶点索引）
	FOR_TEXTURE_PIC,	//顶点信息（三维坐标+二维贴图坐标），索引信息（三点贴图规则索引）
	FOR_TEXTURE_COLOR,	//顶点信息（三维坐标+四维颜色坐标），索引信息（三点贴图规则索引）
	INVALID
}VertexType;

//
typedef struct VertexInfo{
	//图形类型
	VertexType type;
	
	//顶点数据
	int vertexStep;
	int vertexLen;		//每组顶点的长度（顶点数量）
	float *vertexData;	//顶点数据

	//索引数据
	int indexSetNum;	//索引组数量
	int *indexLen;		//每组索引包含索引数据的长度（索引数量）
	int indexSumLen;
	unsigned short *indexData;	//索引数据
}VertexInfo;

class VertexCalc
{
public:
	//顶点信息，每次生成的数据都保存在这里
	VertexInfo m_curVertexInfo;	

	//图形类型
	VertexType type;
	
	//顶点数据
	int vertexStep;
	int vertexLen;		//每组顶点的长度（顶点数量）
	float *vertexData;	//顶点数据

	//索引数据
	int indexSetNum;	//索引组数量
	int *indexLen;		//每组索引包含索引数据的长度（索引数量）
	int indexSumLen;
	unsigned short *indexData;	//索引数据

public:
	VertexCalc();
	~VertexCalc();

	void Init();
	void Destroy();

	//绘制一个矩形（纹理贴图绘制）
	void CreateSquare(int sizex, int sizey, int px, int py, float z = 0);

	//
	void CreateSky(int sizex, int sizey, int px, int py, int index);

	//绘制一个球体（颜色线绘制）
	void CreateSphereLine(int xNum, int yNum, float radius, QVector4D color);

	//绘制一个球体（颜色面绘制）
	void CreateSphereColor(int xNum, int yNum, float radius, QVector4D color);
	void CreateCompleteSphereColor(int xNum, int yNum, float radius, QVector4D color);

	//绘制一个曲面（颜色面绘制）
	void CreateCurvedSurfaceColor(int xNum, int yNum, float radius, QVector4D color, float section);

	//绘制一个圆锥
	void CreateCone(int xNum, float radius, QVector4D color, float section);

	//绘制球体上的一条垂直扫描带
	void CreateSphereBand(int xNum, float radius, QVector4D color, float section);

	//绘制球体上的一条横向扫描带
	//void CreateSphereBand(int xNum, float radius, QVector4D color, float section);

	void CreateLine(QVector3D *point, int pointNum, QVector4D color);

private:
	//
	void CreateSphereVertex(int xNum, int yNum, float radius, QVector4D color);
	void CreateSphereIndex(int xNum, int yNum);

	void CreateCompleteSphereIndex(int xNum, int yNum);

	void CreateCurvedSurfaceVertex(int xNum, int yNum, float radius, QVector4D color, float section);
	void CreateCurvedSurfaceIndex(int xNum, int yNum);

	void CreateConeVertex(int xNum, float radius, QVector4D color, float section);
	void CreateConeIndex(int xNum);

	void CreateSphereBandVertex(int xNum, float radius, QVector4D color, float section);
	void CreateSphereBandIndex(int xNum);

	void CreateLineVertex(QVector3D *point, int pointNum, QVector4D color);
	void CreateLineIndex(int pointNum);

	//极坐标转换为空间直角坐标
	void Polar2Right(float hor, float ver, float radius, float &fx, float &fy, float &fz);
};

#endif