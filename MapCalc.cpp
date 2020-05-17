#include "MapCalc.h"
#include "Config.h"
#include <math.h>
#include <qdebug.h>
#include <qfile.h>
#include <QPainter>

#if defined(_MSC_VER) && (_MSC_VER >= 1600)
# pragma execution_character_set("utf-8")
#endif

MapCalc::MapCalc()
{
	stopped = false;
	m_curMapLevel = 15;
	m_nullImage.load(NULL_MAP_PATH);
	/*qDebug() << NULL_MAP_PATH;*/
}

MapCalc::~MapCalc()
{
	ClearMapImage();
	ClearMapTexture();
}

void MapCalc::run()
{
	QOpenGLTexture* tempTexture = NULL;
	QVector3D vec3d;
	int i = 0, j = 0, k = 0;
	int x = 0, y = 0, level = 0;
	while (!stopped)
	{
		//

		msleep(1000);
	}
}

void MapCalc::stop()
{
	stopped = true;
}

void MapCalc::InitMapCalc(double inputLat, double inputLng)
{
	//WGS84转GCJ02的关键参数
	m_a = 6378245.0;
	m_ee = 0.00669342162296594323;

	//经纬度转瓦片的关键参数
	m_initialResolution = 2 * M_PI * EARTH_RADIUS / MAP_SIZE;	//156543.03392804062 for tileSize 256 pixels  
    m_originShift = 2 * M_PI * EARTH_RADIUS / 2.0;				//20037508.342789244  

	//一个像素对应的墨卡托距离
	m_res = m_initialResolution / pow(2.0, INIT_MAP_LEVEL);
	
	//
	m_initMapLevel = INIT_MAP_LEVEL;
	m_initRes = m_res;

	//一个像素对应的物理距离（米）
	m_resM = m_res * cos(inputLat * M_PI/180);//在特定纬度附近，进行像素点到距离映射的修正（当前地图的距离显示仅在小范围区域内有效）

	//将经纬度换算为瓦片地图x、y索引，在当前瓦片地图上对应的像素偏移x、y位置
	lonLat2Mk(inputLat, inputLng, m_initMkLat, m_initMkLng);

	//Mk2txty(m_curMkLat, m_curMkLng, ZOOM_LEVEL, m_xc, m_yc, m_ppx, m_ppy);

	m_curMkLat = m_initMkLat;	//纬度
	m_curMkLng = m_initMkLng;	//经度
}


//wgs84->cgj02->墨卡托变换
void MapCalc::lonLat2Mk(double wgLat, double wgLng, double &mkLat, double &mkLng)
{
	double tLat = 0, tLng = 0;

	//wgs84转cgj02
	transformWGS2GCJ(wgLat, wgLng, tLat, tLng);

	//经纬度转墨卡托投影
	lonLat2WebMercator(tLat, tLng, mkLat, mkLng);
}

//墨卡托变换->cgj02->wgs84
void MapCalc::Mk2lonLat(double mkLat, double mkLng, double &wgLat, double &wgLng)
{
	double tLat = 0, tLng = 0;

	//墨卡托投影转经纬度
	WebMercator2lonLat(mkLat, mkLng, tLat, tLng);

	//cgj02转wgs84
	//transformGCJ2WGS(tLat, tLng, wgLat, wgLng);
	transformGCJ2WGS_EX(tLat, tLng, wgLat, wgLng);
}

void MapCalc::Normal2Google(int zoomLevel, int &ty, int &ppy)
{
	ty = pow(2.0, zoomLevel) - 1 - ty;//谷歌地图经度瓦片位置变换（coordinate origin is moved from bottom-left to top-left corner of the extent）
	ppy = MAP_SIZE - ppy;
}

void MapCalc::Google2Normal(int zoomLevel, int &ty)
{
	ty = pow(2.0, zoomLevel) - ty;
}

void MapCalc::Mk2txty(double mkLat, double mkLng, int zoomLevel, int &tx, int &ty, int &ppx, int &ppy)
{
	float res = m_initialResolution / pow(2.0, zoomLevel);

	//计算当前经纬度对应的地球地图像素位置
	int px = (mkLng + m_originShift) / res;//经度对应的像素位置
	int py = (mkLat + m_originShift) / res;//维度对应的像素位置

	//判断当前需要加载哪些瓦片地图
	tx = ceil(1.0 * px / MAP_SIZE) - 1;//计算经度对应瓦片位置
	ppx = px - tx * MAP_SIZE;
	ty = ceil(1.0 * py / MAP_SIZE) - 1;//计算维度对应瓦片位置
	ppy = py - ty * MAP_SIZE;

	//谷歌地图瓦片索引计算方式与标准有所不同，需要修正
	Normal2Google(zoomLevel, ty, ppy);
}

void MapCalc::txty2Mk(int tx, int ty, int ppx, int ppy, int zoomLevel, double &mkLat, double &mkLng)
{
	int px = 0, py = 0;
	float res = m_initialResolution / pow(2.0, zoomLevel);

	//谷歌地图瓦片索引计算方式与标准有所不同，需要修正
	Google2Normal(zoomLevel, ty);

	px = tx * MAP_SIZE;
	py = ty * MAP_SIZE;

	mkLng = px * res - m_originShift;
	mkLat = py * res - m_originShift;
}

void MapCalc::Mk2pxpy(double mkLat, double mkLng, int zoomLevel, int &px, int &py)
{
	float res = m_initialResolution / pow(2.0, zoomLevel);

	//计算当前经纬度对应的地球地图像素位置
	int newPx = (mkLng + m_originShift) / res;//经度对应的像素位置
	int newPy = (mkLat + m_originShift) / res;//维度对应的像素位置
	int centerPx = (m_initMkLng + m_originShift) / res;//经度对应的像素位置
	int centerPy = (m_initMkLat + m_originShift) / res;//维度对应的像素位置

	px = newPx - centerPx;
	py = centerPy - newPy;
}

void MapCalc::pxpy2Mk(int px, int py, int zoomLevel, double &mkLat, double &mkLng)
{
	float res = m_initialResolution / pow(2.0, zoomLevel);

	//计算当前经纬度对应的地球地图像素位置
	int centerPx = (m_initMkLng + m_originShift) / res;//经度对应的像素位置
	int centerPy = (m_initMkLat + m_originShift) / res;//维度对应的像素位置

	mkLng = m_initMkLng + px * res;
	mkLat = m_initMkLat + py * res;
}

/************************************************************************/
/* wgs84与墨卡托投影互转                                                */
/************************************************************************/

//经纬度转Wev墨卡托
void MapCalc::lonLat2WebMercator(double srcLat, double srcLng, double &destLat, double &destLng)
{
	double x = log(tan((90+srcLat)*M_PI/360))/(M_PI/180);
	double y = srcLng *20037508.34/180;
	x = x *20037508.34/180;
	destLng = y;
	destLat = x;
}

//Wev墨卡托转经纬度
void MapCalc::WebMercator2lonLat(double srcLat, double srcLng, double &destLat, double &destLng)
{
	double x = srcLat/20037508.34*180;
	double y = srcLng/20037508.34*180;
	x = 180.0/M_PI*(2.0*atan(exp(x*M_PI/180))-M_PI/2);
	destLat = x;
	destLng = y;
}

/************************************************************************/
/* wgs84转gcj02                                                         */
/************************************************************************/

// World Geodetic System ==> Mars Geodetic System
void MapCalc::transformWGS2GCJ(double wgLat, double wgLon, double &mgLat, double &mgLon)
{
	if (outOfChina(wgLat, wgLon))
	{
		mgLat = wgLat;
		mgLon = wgLon;
		return;
	}
	double dLat = transformLat(wgLon - 105.0, wgLat - 35.0);
	double dLon = transformLon(wgLon - 105.0, wgLat - 35.0);
	double radLat = wgLat / 180.0 * M_PI;
	double magic = sin(radLat);
	magic = 1 - m_ee * magic * magic;
	double sqrtMagic = sqrt(magic);
	dLat = (dLat * 180.0) / ((m_a * (1 - m_ee)) / (magic * sqrtMagic) * M_PI);
	dLon = (dLon * 180.0) / (m_a / sqrtMagic * cos(radLat) * M_PI);
	mgLat = wgLat + dLat;
	mgLon = wgLon + dLon;
}

// Mars Geodetic System ==> World Geodetic System
void MapCalc::transformGCJ2WGS(double mgLat, double mgLon, double &wgLat, double &wgLon)
{
	if (outOfChina(mgLat, mgLon))
	{
		wgLat = mgLat;
		wgLon = mgLon;
		return;
	}
	double dLat = transformLat(mgLon - 105.0, mgLat - 35.0);
	double dLon = transformLon(mgLon - 105.0, mgLat - 35.0);
	double radLat = mgLat / 180.0 * M_PI;
	double magic = sin(radLat);
	magic = 1 - m_ee * magic * magic;
	double sqrtMagic = sqrt(magic);
	dLat = (dLat * 180.0) / ((m_a * (1 - m_ee)) / (magic * sqrtMagic) * M_PI);
	dLon = (dLon * 180.0) / (m_a / sqrtMagic * cos(radLat) * M_PI);
	wgLat = mgLat - dLat;
	wgLon = mgLon - dLon;
}
// Mars Geodetic System ==> World Geodetic System (exactly)
void MapCalc::transformGCJ2WGS_EX(double mgLat, double mgLon, double &wgLat, double &wgLon)
{
	float initDelta = 0.01;
	float threshold = 0.000000001;
	double dLat = initDelta, dLon = initDelta;
	float mLat = mgLat - dLat, mLon = mgLon - dLon;
	float pLat = mgLat + dLat, pLon = mgLon + dLon;
	float wgsLat = 0, wgsLon = 0, i = 0;
	while (1) {
		wgsLat = (mLat + pLat) / 2;
		wgsLon = (mLon + pLon) / 2;

		transformWGS2GCJ(wgsLat, wgsLon, dLat, dLon);

		dLat = dLat - mgLat;
		dLon = dLon - mgLon;
		if ((abs(dLat) < threshold) && (abs(dLon) < threshold))
			break;

		if (dLat > 0)
			pLat = wgsLat;
		else
			mLat = wgsLat;

		if (dLon > 0)
			pLon = wgsLon;
		else 
			mLon = wgsLon;

		if (++i > 10000) 
			break;
	}
	wgLat = wgsLat;
	wgLon = wgsLon;
}

bool MapCalc::outOfChina(double lat, double lon)
{
	if (lon < 72.004 || lon > 137.8347)
		return true;
	if (lat < 0.8293 || lat > 55.8271)
		return true;
	return false;
}

double MapCalc::transformLat(double x, double y)
{
	double ret = -100.0 + 2.0 * x + 3.0 * y + 0.2 * y * y + 0.1 * x * y + 0.2 * sqrt(abs(x));
	ret += (20.0 * sin(6.0 * x * M_PI) + 20.0 * sin(2.0 * x * M_PI)) * 2.0 / 3.0;
	ret += (20.0 * sin(y * M_PI) + 40.0 * sin(y / 3.0 * M_PI)) * 2.0 / 3.0;
	ret += (160.0 * sin(y / 12.0 * M_PI) + 320 * sin(y * M_PI / 30.0)) * 2.0 / 3.0;
	return ret;
}

double MapCalc::transformLon(double x, double y)
{
	double ret = 300.0 + x + 2.0 * y + 0.1 * x * x + 0.1 * x * y + 0.1 * sqrt(abs(x));
	ret += (20.0 * sin(6.0 * x * M_PI) + 20.0 * sin(2.0 * x * M_PI)) * 2.0 / 3.0;
	ret += (20.0 * sin(x * M_PI) + 40.0 * sin(x / 3.0 * M_PI)) * 2.0 / 3.0;
	ret += (150.0 * sin(x / 12.0 * M_PI) + 300.0 * sin(x / 30.0 * M_PI)) * 2.0 / 3.0;
	return ret;
}


/*.BH--------------------------------------------------------
**
** 函数名:  Tsd_Grid
**
** 描述:    实现格网坐标与经纬度坐标的相互转换。返回值 : 1表示不正常，0表示正常
**
** 输入参数 :
**    flag : 转换选择，flag=1,根据经纬度坐标得到格网坐标
**    lamdc : 格网中心的经度坐标
**    ksic :  格网中心的纬度坐标
**
** 输入输出参数 : 
**    x :  格网坐标系x坐标
**    y :  格网坐标系y坐标
**    L :  经度坐标
**    B :  纬度坐标
**
** 全局变量 :  
**     无
**  
** 设计注记 :  
**     庞海龙提供的水平角、距离与经纬度互转的程序
**     ※※※※特别注意：不要搞混参数中经纬度的顺序！※※※※
**.EH--------------------------------------------------------
*/
int MapCalc::Tsd_Grid(int flag,double lamdc,double ksic,double *x,double *y,double *B,double *L)
{
	double lamda1=0;
	double nav_r=0;
	double temp1=0;
	double c1=0;
	int    ret=0;

	double tempX = 0, tempY = 0, tempB = 0, tempL = 0;

	/*格网中心的纬度坐标接近90度*/
	//相当于网格中心的坐标点在南极点或北极点附近，此时本坐标转换函数不起作用。
	if(fabs(M_PI/2-fabs(ksic))<(0.5*M_PI/180))
	{  
		return 1;
	} 

	ret=0;
	//地球半径
	nav_r=(NAV_Ea+NAV_Eb)/2;
	if(flag==1)
	{ 
		//经纬度转x、y
		lamda1=asin(sin((*L)-lamdc)*cos(*B));
		if(fabs(cos(lamda1))<1e-15)
		{
			ret=1;
		}
		else
		{
			*x=lamda1*nav_r;
			*y=cos(lamda1)*(asin(sin(*B)/cos(lamda1))-ksic)*nav_r;
		}

#ifdef YS_CALC
		//待验证

		//x方向的相对距离(以正东为正） = 本机与目标的经度夹角（单位弧度）×目标当前纬度所在切面的球面半径
		tempX = (*L-lamdc) * nav_r * cos(*B);

		//y方向的相对距离(以正北为正) = 本机与目标的纬度夹角（单位弧度）×地球半径
		tempY = (*B-ksic) * nav_r;

		*x = tempX;
		*y = tempY;
#endif

	}
	else
	{
		//x、y转经纬度
		temp1=(*x)/nav_r;
		c1=cos(temp1);
		if(fabs(c1)<1e-15)
		{
			ret=1;
		}
		else
		{
			*B=asin(c1*sin(ksic+(*y)/(nav_r*c1)));
			if(fabs(cos(*B))<1e-15)
			{
				ret=1;
			}
			else
			{
				*L=asin(sin(temp1)/cos(*B))+lamdc;
			}
		}

#ifdef YS_CALC
		//待验证

		//本机经度（单位弧度） = （x方向的相对距离(以正东为正）÷ 目标当前纬度所在切面的球面半径） + 目标纬度（单位弧度） 
		tempL = *x / (nav_r * cos(*B)) + lamdc;

		//本机纬度（单位弧度） = （y方向的相对距离(以正北为正） ÷ 地球半径） + 目标经度（单位弧度）
		tempB = *y / nav_r + ksic;

		*B = tempB;
		*L = tempL;
#endif
	}
	return ret;
} 


QImage MapCalc::cvMat2QImage(const cv::Mat& mat)
{
	// 8-bits unsigned, NO. OF CHANNELS = 1
	if (mat.type() == CV_8UC1)
	{
		QImage image(mat.cols, mat.rows, QImage::Format_Indexed8);
		// Set the color table (used to translate colour indexes to qRgb values)
		image.setColorCount(256);
		for (int i = 0; i < 256; i++)
		{
			image.setColor(i, qRgb(i, i, i));
		}
		// Copy input Mat
		uchar *pSrc = mat.data;
		for (int row = 0; row < mat.rows; row++)
		{
			uchar *pDest = image.scanLine(row);
			memcpy(pDest, pSrc, mat.cols);
			pSrc += mat.step;
		}
		return image;
	}
	// 8-bits unsigned, NO. OF CHANNELS = 3
	else if (mat.type() == CV_8UC3)
	{
		// Copy input Mat
		const uchar *pSrc = (const uchar*)mat.data;
		// Create QImage with same dimensions as input Mat
		QImage image(pSrc, mat.cols, mat.rows, mat.step, QImage::Format_RGB888);
		return image.rgbSwapped();
	}
	else if (mat.type() == CV_8UC4)
	{
		//qDebug() << "CV_8UC4";
		// Copy input Mat
		const uchar *pSrc = (const uchar*)mat.data;
		// Create QImage with same dimensions as input Mat
		QImage image(pSrc, mat.cols, mat.rows, mat.step, QImage::Format_ARGB32);
		return image.copy();
	}
	else
	{
		qDebug() << "ERROR: Mat could not be converted to QImage.";
		return QImage();
	}
}

cv::Mat MapCalc::QImage2cvMat(QImage image)
{
	cv::Mat mat;
	//qDebug() << image.format();
	switch (image.format())
	{
	case QImage::Format_ARGB32:
	case QImage::Format_RGB32:
	case QImage::Format_ARGB32_Premultiplied:
		mat = cv::Mat(image.height(), image.width(), CV_8UC4, (void*)image.constBits(), image.bytesPerLine());
		break;
	case QImage::Format_RGB888:
		mat = cv::Mat(image.height(), image.width(), CV_8UC3, (void*)image.constBits(), image.bytesPerLine());
		cv::cvtColor(mat, mat, CV_BGR2RGB);//
		break;
	case QImage::Format_Indexed8:
		mat = cv::Mat(image.height(), image.width(), CV_8UC1, (void*)image.constBits(), image.bytesPerLine());
		break;
	}
	return mat;
}

//获取瓦片地图
QImage* MapCalc::GetMapImage(int level, int x, int y)
{
	QString tempPath, tempLightPath;
	QImage *newImage = NULL;

	QMap<int, QImage*>* tempQMap;
	int key1 = level * 1e5 + x;
	int key2 = y;

	//一级索引
	if (!m_mapImage.contains(key1))
	{
		tempQMap = new QMap<int, QImage*>;
		m_mapImage.insert(key1, tempQMap);
	}
	else
		tempQMap = m_mapImage[key1];

	//二级索引
	if (!tempQMap->contains(key2))
	{
		if (level >= PATH_11_16_MIN && level <= PATH_11_16_MAX)
		{
			tempPath.sprintf("%s/%d/%d_%d_%d_s.png", MAP_PATH_PRE_11_16, level, level, x, y);
		}
		else if (level >= PATH_0_10_MIN && level <= PATH_0_10_MAX)
		{
			tempPath.sprintf("%s/%d/%d_%d_%d_s.png", MAP_PATH_PRE_0_10, level, level, x, y);
#if 0
			tempLightPath.sprintf("%s/%d/%d_%d_%d_s.png", MAP_LIGHT_PRE, level, level, x, y);
#endif
		}

		if (QFile::exists(tempPath))
		{
			newImage = new QImage(tempPath);
#if 0
			if (QFile::exists(tempLightPath))
			{
				QPixmap tempPixmap(tempLightPath);
				QPainter p(newImage);
				p.drawPixmap(0, 0, tempPixmap);
			}
#endif
		}
		else
		{
			newImage = NULL;
			if (QFile::exists(tempLightPath))
			{
				newImage = new QImage(tempLightPath);
			}
		}

		tempQMap->insert(key2, newImage);
		return newImage;
	}
	else
	{
		return (*tempQMap)[key2];
	}
}

//清空瓦片地图池
void MapCalc::ClearMapImage()
{
	QMapIterator<int, QMap<int, QImage*>*> i(m_mapImage);
	QMap<int, QImage*>* tempQMap;
	while (i.hasNext()) {
		i.next();
		tempQMap = i.value();

		QMapIterator<int, QImage*> j(*tempQMap);
		while (j.hasNext())
		{
			j.next();
			delete j.value();
		}

		delete tempQMap;
	}
	m_mapImage.clear();
}

QOpenGLTexture* MapCalc::GetMapTexture(int level, int x, int y)
{
	QMap<int, QOpenGLTexture*>* tempQTexture = NULL;

	int key1 = level * 1e5 + x;
	int key2 = y;

	//一级索引
	if (!m_mapTexturePool.contains(key1))
		return NULL;
	else
		tempQTexture = m_mapTexturePool[key1];

	//二级索引
	if (tempQTexture->contains(key2))
	{
		//qDebug() << "get a texture";
		return (*tempQTexture)[key2]; 
	}
	else
		return NULL;
}

//地图纹理区域设置说明
//暂定使用瓦片地图的地图等级范围为4~16，第16级的x、y的最大索引位65536
//地图纹理区域暂时采用16*16个图片作为一个瓦片地图纹理区域，形成的索引技法等同于瓦片地图等级减去4的索引技法
QOpenGLTexture* MapCalc::SetMapTexture(int level, int x, int y)
{
	QImage tempQImage;
	QOpenGLTexture *newTexture = NULL;
	QMap<int, QOpenGLTexture*>* tempQTexture;
	int minX = 0, maxX = 0, minY = 0, maxY = 0;
	int key1 = level * 1e5 + x;
	int key2 = y;
	
	//一级索引
	if (!m_mapTexturePool.contains(key1))
	{
		tempQTexture = new QMap<int, QOpenGLTexture*>;
		m_mapTexturePool.insert(key1, tempQTexture);
	}
	else
		tempQTexture = m_mapTexturePool[key1];

	//二级索引
	if (tempQTexture->contains(key2))
	{
		return (*tempQTexture)[key2];
	}
	else
	{
		minX = x;
		maxX = x;
		minY = y;
		maxY = y;

		newTexture = CreateMapTexture(level, minX, maxX, minY, maxY);
		tempQTexture->insert(key2, newTexture);

		//qDebug() << "add a texture";

		return newTexture;
	}
}

int MapCalc::SetMapTexture(int level, int x, int y, QOpenGLTexture *texture)
{
	QImage *tempImage = GetMapImage(level, x, y);
	if (texture != NULL && tempImage != NULL)
	{
		//采用实时更换texture中数据的方法，性能比保存已加载的texture性能更差
		texture->setData(*tempImage, QOpenGLTexture::DontGenerateMipMaps);

		return 1;
	}

	return 0;
}


//清空地图纹理数据池
void MapCalc::ClearMapTexture()
{
	QMapIterator<int, QMap<int, QOpenGLTexture*>*> i(m_mapTexturePool);
	QMap<int, QOpenGLTexture*>* tempQTexture;
	while (i.hasNext()) {
		i.next();
		tempQTexture = i.value();

		QMapIterator<int, QOpenGLTexture*> j(*tempQTexture);
		while (j.hasNext())
		{
			j.next();
			delete j.value();
		}

		delete tempQTexture;
	}
	m_mapImage.clear();
}

//创建指定区域的地图纹理数据
QOpenGLTexture* MapCalc::CreateMapTexture(int level, int minX, int maxX, int minY, int maxY)
{
	int x = 0, y = 0, z = 0;
	QOpenGLTexture *newTexture = NULL;
	cv::Mat tempMat(MAP_SIZE, MAP_SIZE, CV_8UC4);
	cv::Mat mat((maxY - minY + 1) * MAP_SIZE, (maxX - minX + 1) * MAP_SIZE, CV_8UC4);
	QImage* tempImage;

	if (maxX == minX && minY == maxY)
	{
		x = minX;
		y = minY;

		tempImage = GetMapImage(level, x, y);
		if (tempImage != NULL)
		{
			newTexture = new QOpenGLTexture(*tempImage, QOpenGLTexture::DontGenerateMipMaps);
		}
		else
		{
			newTexture = new QOpenGLTexture(m_nullImage, QOpenGLTexture::DontGenerateMipMaps);
		}
	}
	else
	{
		for (x = minX; x <= maxX; x++)
		{
			for (y = minY; y <= maxY; y++)
			{
				tempImage = GetMapImage(level, x, y);
				if (tempImage != NULL)
				{
					tempMat = QImage2cvMat(*tempImage);
					for (z = 0; z < MAP_SIZE; z++)
					{
						memcpy(mat.data + 4 * ((z + (y - minY) * MAP_SIZE) * (maxX - minX + 1) * MAP_SIZE + (x - minX) * MAP_SIZE),
							tempMat.data + 4 * z * MAP_SIZE, 4 * MAP_SIZE);
					}
				}
				else
				{
					tempMat = QImage2cvMat(m_nullImage);
					for (z = 0; z < MAP_SIZE; z++)
					{
						memcpy(mat.data + 4 * ((z + (y - minY) * MAP_SIZE) * (maxX - minX + 1) * MAP_SIZE + (x - minX) * MAP_SIZE),
							tempMat.data + 4 * z * MAP_SIZE, 4 * MAP_SIZE);
					}
				}
			}
		}
		newTexture = new QOpenGLTexture(cvMat2QImage(mat), QOpenGLTexture::DontGenerateMipMaps);
	}

	newTexture->setMinificationFilter(QOpenGLTexture::Linear);
	newTexture->setMagnificationFilter(QOpenGLTexture::Linear);
	newTexture->setWrapMode(QOpenGLTexture::ClampToEdge);

	return newTexture;
}

void MapCalc::SetMapLevel(int level)
{
	m_curMapLevel = level;
	m_res = m_initialResolution / pow(2.0, m_curMapLevel);
}

void MapCalc::SetXYPias(float piasX, float piasY)
{
	float limit = 10000;

	float mklat = m_curMkLat - piasY * m_initRes;//纬度
	float mklng = m_curMkLng + piasX * m_initRes;//经度

	//if (mklat < (m_initMkLat + limit) && mklat >(m_initMkLat - limit))
	{
		m_curMkLat = mklat;
	}
	//if (mklng < (m_initMkLng + limit) && mklng >(m_initMkLng - limit))
	{
		m_curMkLng = mklng;
	}
}

void MapCalc::GetNewLatLng(float piasX, float piasY, float &lat, float &lng)
{
	//
	double destLat = 0, destLng = 0;

	//纬度
	float tempLat = m_curMkLat - piasY * m_initRes;

	//经度
	float tempLng = m_curMkLng + piasX * m_initRes;

	//
	Mk2lonLat(tempLat, tempLng, destLat, destLng);

	lat = destLat;
	lng = destLng;
}

void MapCalc::GetMkLatLng(float piasX, float piasY, float &lat, float &lng)
{
	//纬度
	lat = m_curMkLat - piasY * m_initRes;

	//经度
	lng = m_curMkLng + piasX * m_initRes;
}

//
float MapCalc::GetMkDis(float lat, float dis)
{
	float resM, mkDis;
	resM = m_initRes * cos(lat * M_PI / 180);
	mkDis = dis / resM;
	return mkDis;
}

float MapCalc::GetDis(float lat, float mkdis)
{
	float resM = m_initRes * cos(lat * M_PI / 180);
	float dis = mkdis * resM;
	return dis;
}

void MapCalc::ResetLocation()
{
	m_curMkLat = m_initMkLat;//纬度
	m_curMkLng = m_initMkLng;//经度
}

void MapCalc::SetCenterMkLat(float lat)
{
	m_curMkLat = lat;//纬度
}

void MapCalc::SetCenterMkLng(float lng)
{
	m_curMkLng = lng;//经度
}