#ifndef VERTEXCALC_H
#define VERTEXCALC_H

#include "Config.h"
#include <stdlib.h>
#include <string>
#include <QVector3D>
#include <QVector4D>

//Ŀǰ��������Чģ������
typedef enum{
	FOR_LINES = 1,		//������Ϣ����ά����+��ά��ɫ���꣩��������Ϣ���ɶԵĶ���������
	FOR_TEXTURE_PIC,	//������Ϣ����ά����+��ά��ͼ���꣩��������Ϣ��������ͼ����������
	FOR_TEXTURE_COLOR,	//������Ϣ����ά����+��ά��ɫ���꣩��������Ϣ��������ͼ����������
	INVALID
}VertexType;

//
typedef struct VertexInfo{
	//ͼ������
	VertexType type;
	
	//��������
	int vertexStep;
	int vertexLen;		//ÿ�鶥��ĳ��ȣ�����������
	float *vertexData;	//��������

	//��������
	int indexSetNum;	//����������
	int *indexLen;		//ÿ�����������������ݵĳ��ȣ�����������
	int indexSumLen;
	unsigned short *indexData;	//��������
}VertexInfo;

class VertexCalc
{
public:
	//������Ϣ��ÿ�����ɵ����ݶ�����������
	VertexInfo m_curVertexInfo;	

	//ͼ������
	VertexType type;
	
	//��������
	int vertexStep;
	int vertexLen;		//ÿ�鶥��ĳ��ȣ�����������
	float *vertexData;	//��������

	//��������
	int indexSetNum;	//����������
	int *indexLen;		//ÿ�����������������ݵĳ��ȣ�����������
	int indexSumLen;
	unsigned short *indexData;	//��������

public:
	VertexCalc();
	~VertexCalc();

	void Init();
	void Destroy();

	//����һ�����Σ�������ͼ���ƣ�
	void CreateSquare(int sizex, int sizey, int px, int py, float z = 0);

	//
	void CreateSky(int sizex, int sizey, int px, int py, int index);

	//����һ�����壨��ɫ�߻��ƣ�
	void CreateSphereLine(int xNum, int yNum, float radius, QVector4D color);

	//����һ�����壨��ɫ����ƣ�
	void CreateSphereColor(int xNum, int yNum, float radius, QVector4D color);
	void CreateCompleteSphereColor(int xNum, int yNum, float radius, QVector4D color);

	//����һ�����棨��ɫ����ƣ�
	void CreateCurvedSurfaceColor(int xNum, int yNum, float radius, QVector4D color, float section);

	//����һ��Բ׶
	void CreateCone(int xNum, float radius, QVector4D color, float section);

	//���������ϵ�һ����ֱɨ���
	void CreateSphereBand(int xNum, float radius, QVector4D color, float section);

	//���������ϵ�һ������ɨ���
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

	//������ת��Ϊ�ռ�ֱ������
	void Polar2Right(float hor, float ver, float radius, float &fx, float &fy, float &fz);
};

#endif