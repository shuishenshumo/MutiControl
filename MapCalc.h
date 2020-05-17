#ifndef MAPCLAC_H
#define MAPCALC_H

#include <QOpenGLTexture>
#include <QThread>
#include <QMap>
#include <QImage>
#include <QVector3D>

//OpenCV
#include <QImage>
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

class MapCalc : public QThread
{
	Q_OBJECT

public:
	MapCalc();
	~MapCalc();

	void stop();
protected:
	void run();

private:
	volatile bool stopped;

public:
	//��ǰ��ͼ�ȼ��£�һ�����ص��Ӧ��ī���о���
	double m_res;

	//��ǰ��ͼ�ȼ��£�һ�����ص��Ӧ��������루�ף�
	double m_resM;

	//��ʼ����ͼ���ľ�γ�ȣ�����CGJ02���ܺ��ī����ͶӰ��ʽ��
	double m_initMkLng;//����
	double m_initMkLat;//γ��

	//
	double m_curMkLng;//����
	double m_curMkLat;//γ��

public:
	//��ʼ����ͼ����
	void InitMapCalc(double inputLat, double inputLng);

	//wgs84->cgj02->ī���б任
	void lonLat2Mk(double wgLat, double wgLng, double &mkLat, double &mkLng);						

	//ī���б任->cgj02->wgs84
	void Mk2lonLat(double mkLat, double mkLng, double &wgLat, double &wgLng);

	//�Ӻ����ṩ��ˮƽ�ǡ������뾭γ�Ȼ�ת�ĳ���
	//���������ر�ע�⣺��Ҫ�������о�γ�ȵ�˳�򣡡�������
	int Tsd_Grid(int flag,double lamdc,double ksic,double *x,double *y,double *B,double *L);

	// �� wgs84->cgj02 �����ӻ�������down�����ģ�ֻ����һ�β��ԣ������3m���ң�������˵�����10m���£�
	// Krasovsky 1940
	// a = 6378245.0, 1/f = 298.3
	// b = a * (1 - f)
	// ee = (a^2 - b^2) / a^2;
	double m_a;
	double m_ee;
	void transformWGS2GCJ(double wgLat, double wgLon, double &mgLat, double &mgLon);
	void transformGCJ2WGS(double mgLat, double mgLon, double &wgLat, double &wgLon);
	void transformGCJ2WGS_EX(double mgLat, double mgLon, double &wgLat, double &wgLon);
	bool outOfChina(double lat, double lon);
	double transformLat(double x, double y);
	double transformLon(double x, double y);

	//
	void Normal2Google(int zoomLevel, int &ty, int &ppy);//google��ͼ�������㷽ʽ����	
	void Google2Normal(int zoomLevel, int &ty);//google��ͼ�������㷽ʽ����
	void Mk2txty(double mkLat, double mkLng, int zoomLevel, int &tx, int &ty, int &ppx, int &ppy);	//ī����ͶӰ->ͼƬ��ƫ������λ��
	void txty2Mk(int tx, int ty, int ppx, int ppy, int zoomLevel, double &mkLat, double &mkLng);	//ͼƬλ��->ī����ͶӰ
	void Mk2pxpy(double mkLat, double mkLng, int zoomLevel, int &px, int &py);						//ī����ͶӰ->scence����λ��
	void pxpy2Mk(int px, int py, int zoomLevel, double &mkLat, double &mkLng);						//scence����λ��->ī����ͶӰ

private:
	//0����ͼ�£�ÿ�����ض�Ӧ�ľ���
	double m_initialResolution;	

	//�����ܳ���һ��
	double m_originShift;

	//WGS-84��γ��--->ī����ͶӰ
	void lonLat2WebMercator(double srcLat, double srcLng, double &destLat, double &destLng);

	//ī����ͶӰ--->WGS-84��γ��
	void WebMercator2lonLat(double srcLat, double stcLng, double &destLat, double &destLng);	

public:
	//��ͼ���ݻ���ӳ��
	QMap<int, QMap<int, QImage*>*> m_mapImage;				//��Ƭ��ͼ��
	QImage* GetMapImage(int level, int x, int y);
	void ClearMapImage();

	//��ͼ�������ݳ�
	QMap<int, QMap<int, QOpenGLTexture*>*> m_mapTexturePool;
	QOpenGLTexture* GetMapTexture(int level, int x, int y);
	QOpenGLTexture* SetMapTexture(int level, int x, int y);
	int SetMapTexture(int level, int x, int y, QOpenGLTexture *texture);
	QOpenGLTexture* CreateMapTexture(int level, int minX, int maxX, int minY, int maxY);
	void ClearMapTexture();

	//OpenCV���
	//����QImage��OpenCV��mat��ʽ��ת
	QImage cvMat2QImage(const cv::Mat& mat);
	cv::Mat QImage2cvMat(QImage image);

	//
	int m_initMapLevel;
	double m_initRes;

	int m_curMapLevel;
	QImage m_nullImage;
	
	void SetMapLevel(int level);
	void SetXYPias(float piasX, float piasY);
	void GetMkLatLng(float piasX, float piasY, float &lat, float &lng);
	void GetNewLatLng(float piasX, float piasY, float &lat, float &lng);
	float GetMkDis(float lat, float dis);
	float GetDis(float lat, float mkdis);

	void ResetLocation();

	void SetCenterMkLat(float lat);
	void SetCenterMkLng(float lng);
};


#endif