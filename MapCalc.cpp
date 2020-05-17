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
	//WGS84תGCJ02�Ĺؼ�����
	m_a = 6378245.0;
	m_ee = 0.00669342162296594323;

	//��γ��ת��Ƭ�Ĺؼ�����
	m_initialResolution = 2 * M_PI * EARTH_RADIUS / MAP_SIZE;	//156543.03392804062 for tileSize 256 pixels  
    m_originShift = 2 * M_PI * EARTH_RADIUS / 2.0;				//20037508.342789244  

	//һ�����ض�Ӧ��ī���о���
	m_res = m_initialResolution / pow(2.0, INIT_MAP_LEVEL);
	
	//
	m_initMapLevel = INIT_MAP_LEVEL;
	m_initRes = m_res;

	//һ�����ض�Ӧ��������루�ף�
	m_resM = m_res * cos(inputLat * M_PI/180);//���ض�γ�ȸ������������ص㵽����ӳ�����������ǰ��ͼ�ľ�����ʾ����С��Χ��������Ч��

	//����γ�Ȼ���Ϊ��Ƭ��ͼx��y�������ڵ�ǰ��Ƭ��ͼ�϶�Ӧ������ƫ��x��yλ��
	lonLat2Mk(inputLat, inputLng, m_initMkLat, m_initMkLng);

	//Mk2txty(m_curMkLat, m_curMkLng, ZOOM_LEVEL, m_xc, m_yc, m_ppx, m_ppy);

	m_curMkLat = m_initMkLat;	//γ��
	m_curMkLng = m_initMkLng;	//����
}


//wgs84->cgj02->ī���б任
void MapCalc::lonLat2Mk(double wgLat, double wgLng, double &mkLat, double &mkLng)
{
	double tLat = 0, tLng = 0;

	//wgs84תcgj02
	transformWGS2GCJ(wgLat, wgLng, tLat, tLng);

	//��γ��תī����ͶӰ
	lonLat2WebMercator(tLat, tLng, mkLat, mkLng);
}

//ī���б任->cgj02->wgs84
void MapCalc::Mk2lonLat(double mkLat, double mkLng, double &wgLat, double &wgLng)
{
	double tLat = 0, tLng = 0;

	//ī����ͶӰת��γ��
	WebMercator2lonLat(mkLat, mkLng, tLat, tLng);

	//cgj02תwgs84
	//transformGCJ2WGS(tLat, tLng, wgLat, wgLng);
	transformGCJ2WGS_EX(tLat, tLng, wgLat, wgLng);
}

void MapCalc::Normal2Google(int zoomLevel, int &ty, int &ppy)
{
	ty = pow(2.0, zoomLevel) - 1 - ty;//�ȸ��ͼ������Ƭλ�ñ任��coordinate origin is moved from bottom-left to top-left corner of the extent��
	ppy = MAP_SIZE - ppy;
}

void MapCalc::Google2Normal(int zoomLevel, int &ty)
{
	ty = pow(2.0, zoomLevel) - ty;
}

void MapCalc::Mk2txty(double mkLat, double mkLng, int zoomLevel, int &tx, int &ty, int &ppx, int &ppy)
{
	float res = m_initialResolution / pow(2.0, zoomLevel);

	//���㵱ǰ��γ�ȶ�Ӧ�ĵ����ͼ����λ��
	int px = (mkLng + m_originShift) / res;//���ȶ�Ӧ������λ��
	int py = (mkLat + m_originShift) / res;//ά�ȶ�Ӧ������λ��

	//�жϵ�ǰ��Ҫ������Щ��Ƭ��ͼ
	tx = ceil(1.0 * px / MAP_SIZE) - 1;//���㾭�ȶ�Ӧ��Ƭλ��
	ppx = px - tx * MAP_SIZE;
	ty = ceil(1.0 * py / MAP_SIZE) - 1;//����ά�ȶ�Ӧ��Ƭλ��
	ppy = py - ty * MAP_SIZE;

	//�ȸ��ͼ��Ƭ�������㷽ʽ���׼������ͬ����Ҫ����
	Normal2Google(zoomLevel, ty, ppy);
}

void MapCalc::txty2Mk(int tx, int ty, int ppx, int ppy, int zoomLevel, double &mkLat, double &mkLng)
{
	int px = 0, py = 0;
	float res = m_initialResolution / pow(2.0, zoomLevel);

	//�ȸ��ͼ��Ƭ�������㷽ʽ���׼������ͬ����Ҫ����
	Google2Normal(zoomLevel, ty);

	px = tx * MAP_SIZE;
	py = ty * MAP_SIZE;

	mkLng = px * res - m_originShift;
	mkLat = py * res - m_originShift;
}

void MapCalc::Mk2pxpy(double mkLat, double mkLng, int zoomLevel, int &px, int &py)
{
	float res = m_initialResolution / pow(2.0, zoomLevel);

	//���㵱ǰ��γ�ȶ�Ӧ�ĵ����ͼ����λ��
	int newPx = (mkLng + m_originShift) / res;//���ȶ�Ӧ������λ��
	int newPy = (mkLat + m_originShift) / res;//ά�ȶ�Ӧ������λ��
	int centerPx = (m_initMkLng + m_originShift) / res;//���ȶ�Ӧ������λ��
	int centerPy = (m_initMkLat + m_originShift) / res;//ά�ȶ�Ӧ������λ��

	px = newPx - centerPx;
	py = centerPy - newPy;
}

void MapCalc::pxpy2Mk(int px, int py, int zoomLevel, double &mkLat, double &mkLng)
{
	float res = m_initialResolution / pow(2.0, zoomLevel);

	//���㵱ǰ��γ�ȶ�Ӧ�ĵ����ͼ����λ��
	int centerPx = (m_initMkLng + m_originShift) / res;//���ȶ�Ӧ������λ��
	int centerPy = (m_initMkLat + m_originShift) / res;//ά�ȶ�Ӧ������λ��

	mkLng = m_initMkLng + px * res;
	mkLat = m_initMkLat + py * res;
}

/************************************************************************/
/* wgs84��ī����ͶӰ��ת                                                */
/************************************************************************/

//��γ��תWevī����
void MapCalc::lonLat2WebMercator(double srcLat, double srcLng, double &destLat, double &destLng)
{
	double x = log(tan((90+srcLat)*M_PI/360))/(M_PI/180);
	double y = srcLng *20037508.34/180;
	x = x *20037508.34/180;
	destLng = y;
	destLat = x;
}

//Wevī����ת��γ��
void MapCalc::WebMercator2lonLat(double srcLat, double srcLng, double &destLat, double &destLng)
{
	double x = srcLat/20037508.34*180;
	double y = srcLng/20037508.34*180;
	x = 180.0/M_PI*(2.0*atan(exp(x*M_PI/180))-M_PI/2);
	destLat = x;
	destLng = y;
}

/************************************************************************/
/* wgs84תgcj02                                                         */
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
** ������:  Tsd_Grid
**
** ����:    ʵ�ָ��������뾭γ��������໥ת��������ֵ : 1��ʾ��������0��ʾ����
**
** ������� :
**    flag : ת��ѡ��flag=1,���ݾ�γ������õ���������
**    lamdc : �������ĵľ�������
**    ksic :  �������ĵ�γ������
**
** ����������� : 
**    x :  ��������ϵx����
**    y :  ��������ϵy����
**    L :  ��������
**    B :  γ������
**
** ȫ�ֱ��� :  
**     ��
**  
** ���ע�� :  
**     �Ӻ����ṩ��ˮƽ�ǡ������뾭γ�Ȼ�ת�ĳ���
**     ���������ر�ע�⣺��Ҫ�������о�γ�ȵ�˳�򣡡�������
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

	/*�������ĵ�γ������ӽ�90��*/
	//�൱���������ĵ���������ϼ���򱱼��㸽������ʱ������ת�������������á�
	if(fabs(M_PI/2-fabs(ksic))<(0.5*M_PI/180))
	{  
		return 1;
	} 

	ret=0;
	//����뾶
	nav_r=(NAV_Ea+NAV_Eb)/2;
	if(flag==1)
	{ 
		//��γ��תx��y
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
		//����֤

		//x�������Ծ���(������Ϊ���� = ������Ŀ��ľ��ȼнǣ���λ���ȣ���Ŀ�굱ǰγ���������������뾶
		tempX = (*L-lamdc) * nav_r * cos(*B);

		//y�������Ծ���(������Ϊ��) = ������Ŀ���γ�ȼнǣ���λ���ȣ�������뾶
		tempY = (*B-ksic) * nav_r;

		*x = tempX;
		*y = tempY;
#endif

	}
	else
	{
		//x��yת��γ��
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
		//����֤

		//�������ȣ���λ���ȣ� = ��x�������Ծ���(������Ϊ������ Ŀ�굱ǰγ���������������뾶�� + Ŀ��γ�ȣ���λ���ȣ� 
		tempL = *x / (nav_r * cos(*B)) + lamdc;

		//����γ�ȣ���λ���ȣ� = ��y�������Ծ���(������Ϊ���� �� ����뾶�� + Ŀ�꾭�ȣ���λ���ȣ�
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

//��ȡ��Ƭ��ͼ
QImage* MapCalc::GetMapImage(int level, int x, int y)
{
	QString tempPath, tempLightPath;
	QImage *newImage = NULL;

	QMap<int, QImage*>* tempQMap;
	int key1 = level * 1e5 + x;
	int key2 = y;

	//һ������
	if (!m_mapImage.contains(key1))
	{
		tempQMap = new QMap<int, QImage*>;
		m_mapImage.insert(key1, tempQMap);
	}
	else
		tempQMap = m_mapImage[key1];

	//��������
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

//�����Ƭ��ͼ��
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

	//һ������
	if (!m_mapTexturePool.contains(key1))
		return NULL;
	else
		tempQTexture = m_mapTexturePool[key1];

	//��������
	if (tempQTexture->contains(key2))
	{
		//qDebug() << "get a texture";
		return (*tempQTexture)[key2]; 
	}
	else
		return NULL;
}

//��ͼ������������˵��
//�ݶ�ʹ����Ƭ��ͼ�ĵ�ͼ�ȼ���ΧΪ4~16����16����x��y���������λ65536
//��ͼ����������ʱ����16*16��ͼƬ��Ϊһ����Ƭ��ͼ���������γɵ�����������ͬ����Ƭ��ͼ�ȼ���ȥ4����������
QOpenGLTexture* MapCalc::SetMapTexture(int level, int x, int y)
{
	QImage tempQImage;
	QOpenGLTexture *newTexture = NULL;
	QMap<int, QOpenGLTexture*>* tempQTexture;
	int minX = 0, maxX = 0, minY = 0, maxY = 0;
	int key1 = level * 1e5 + x;
	int key2 = y;
	
	//һ������
	if (!m_mapTexturePool.contains(key1))
	{
		tempQTexture = new QMap<int, QOpenGLTexture*>;
		m_mapTexturePool.insert(key1, tempQTexture);
	}
	else
		tempQTexture = m_mapTexturePool[key1];

	//��������
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
		//����ʵʱ����texture�����ݵķ��������ܱȱ����Ѽ��ص�texture���ܸ���
		texture->setData(*tempImage, QOpenGLTexture::DontGenerateMipMaps);

		return 1;
	}

	return 0;
}


//��յ�ͼ�������ݳ�
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

//����ָ������ĵ�ͼ��������
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

	float mklat = m_curMkLat - piasY * m_initRes;//γ��
	float mklng = m_curMkLng + piasX * m_initRes;//����

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

	//γ��
	float tempLat = m_curMkLat - piasY * m_initRes;

	//����
	float tempLng = m_curMkLng + piasX * m_initRes;

	//
	Mk2lonLat(tempLat, tempLng, destLat, destLng);

	lat = destLat;
	lng = destLng;
}

void MapCalc::GetMkLatLng(float piasX, float piasY, float &lat, float &lng)
{
	//γ��
	lat = m_curMkLat - piasY * m_initRes;

	//����
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
	m_curMkLat = m_initMkLat;//γ��
	m_curMkLng = m_initMkLng;//����
}

void MapCalc::SetCenterMkLat(float lat)
{
	m_curMkLat = lat;//γ��
}

void MapCalc::SetCenterMkLng(float lng)
{
	m_curMkLng = lng;//����
}