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
	//当前地图等级下，一个像素点对应的墨卡托距离
	double m_res;

	//当前地图等级下，一个像素点对应的物理距离（米）
	double m_resM;

	//初始化地图中心经纬度（经过CGJ02加密后的墨卡托投影格式）
	double m_initMkLng;//经度
	double m_initMkLat;//纬度

	//
	double m_curMkLng;//经度
	double m_curMkLat;//纬度

public:
	//初始化地图计算
	void InitMapCalc(double inputLat, double inputLng);

	//wgs84->cgj02->墨卡托变换
	void lonLat2Mk(double wgLat, double wgLng, double &mkLat, double &mkLng);						

	//墨卡托变换->cgj02->wgs84
	void Mk2lonLat(double mkLat, double mkLng, double &wgLat, double &wgLng);

	//庞海龙提供的水平角、距离与经纬度互转的程序
	//※※※※特别注意：不要搞混参数中经纬度的顺序！※※※※
	int Tsd_Grid(int flag,double lamdc,double ksic,double *x,double *y,double *B,double *L);

	// ※ wgs84->cgj02 ※（从互联网上down下来的，只做过一次测试，误差在3m左右，据网上说误差在10m以下）
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
	void Normal2Google(int zoomLevel, int &ty, int &ppy);//google地图索引计算方式修正	
	void Google2Normal(int zoomLevel, int &ty);//google地图索引计算方式修正
	void Mk2txty(double mkLat, double mkLng, int zoomLevel, int &tx, int &ty, int &ppx, int &ppy);	//墨卡托投影->图片与偏移像素位置
	void txty2Mk(int tx, int ty, int ppx, int ppy, int zoomLevel, double &mkLat, double &mkLng);	//图片位置->墨卡托投影
	void Mk2pxpy(double mkLat, double mkLng, int zoomLevel, int &px, int &py);						//墨卡托投影->scence像素位置
	void pxpy2Mk(int px, int py, int zoomLevel, double &mkLat, double &mkLng);						//scence像素位置->墨卡托投影

private:
	//0级地图下，每个像素对应的距离
	double m_initialResolution;	

	//地球周长的一半
	double m_originShift;

	//WGS-84经纬度--->墨卡托投影
	void lonLat2WebMercator(double srcLat, double srcLng, double &destLat, double &destLng);

	//墨卡托投影--->WGS-84经纬度
	void WebMercator2lonLat(double srcLat, double stcLng, double &destLat, double &destLng);	

public:
	//地图数据缓存映射
	QMap<int, QMap<int, QImage*>*> m_mapImage;				//瓦片地图池
	QImage* GetMapImage(int level, int x, int y);
	void ClearMapImage();

	//地图纹理数据池
	QMap<int, QMap<int, QOpenGLTexture*>*> m_mapTexturePool;
	QOpenGLTexture* GetMapTexture(int level, int x, int y);
	QOpenGLTexture* SetMapTexture(int level, int x, int y);
	int SetMapTexture(int level, int x, int y, QOpenGLTexture *texture);
	QOpenGLTexture* CreateMapTexture(int level, int minX, int maxX, int minY, int maxY);
	void ClearMapTexture();

	//OpenCV相关
	//用于QImage与OpenCV的mat格式互转
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