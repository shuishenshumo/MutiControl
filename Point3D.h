#ifndef POINT3D_H
#define POINT3D_H

//=============================================================================
//                         I N C L U D E  F I L E S
//=============================================================================

#include <iostream>
#include "CVector.h"

//=============================================================================
//                                 C L A S S
//=============================================================================

class Point3D
{
public:

	Point3D(const double& a_rX = 0.0, const double& a_rY = 0.0, const double& a_rZ = 0.0);
	Point3D(CVector pV){ m_x = pV.getX(); m_y = pV.getY(); m_z = pV.getZ();}
	virtual ~Point3D(){}

	double* getPtr() {return &m_x;}
	const double* getPtr() const {return &m_x;}

	double getX() const {return m_x;}
	double getY() const {return m_y;}
	double getZ() const {return m_z;}

	void vSetX(const double& a_rx) {m_x = a_rx;}
	void vSetY(const double& a_ry) {m_y = a_ry;}
	void vSetZ(const double& a_rz) {m_z = a_rz;}

	Point3D operator + (CVector & a_rV)
	{ return Point3D(m_x+a_rV.getX(), m_y+a_rV.getY(), m_z+a_rV.getZ()); }

	void operator+=(const CVector& a_rV){m_x+=a_rV.getX();m_y+=a_rV.getY();m_z+=a_rV.getZ();}

private:
	
	double m_x;
	double m_y;
	double m_z;
};

#endif

// End of File
