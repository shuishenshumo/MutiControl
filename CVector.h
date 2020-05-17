#ifndef CVECTOR_H
#define CVECTOR_H

#pragma once

//=============================================================================
//                         I N C L U D E  F I L E S
//=============================================================================

#include <math.h>
#include "Macros.h"

class Point3D;

//
// @class CVector
// @brief defines a 3d vector
//

class CVector
{
public:
	
	CVector(double a_x = 0.0, double a_y = 0.0, double a_z = 0.0);
	CVector(const Point3D & a_rStart, const Point3D & a_rEnd);
	CVector(const CVector& a_rV) {*this = a_rV;}
	virtual ~CVector(){}

	CVector operator / (const double a_value) const;
	const CVector & operator = (const CVector & a_rright);
	CVector operator+(const CVector& a_rRight) const;
	CVector operator-(const CVector& a_rRight) const;
	CVector operator*(const double a_value) const;
	void operator+=(const CVector& a_rRight);

	double dotProduct(const CVector& a_rB);
	CVector crossProduct(const CVector& a_rB) const;

	bool normalize();

	Point3D getEnd(const Point3D& start) const;
	double getNorm()	const;
	double getX()const {return m_x;}
	double getY()const {return m_y;}
	double getZ()const {return m_z;}
	bool   getPhiNegatif()const {return m_phiNegative;}

	void vSetX(const double& a_rx) {m_x = a_rx;}
	void vSetY(const double& a_ry) {m_y = a_ry;}
	void vSetZ(const double& a_rz) {m_z = a_rz;}
	void vSetXYZ(const double& a_rx, const double& a_ry, const double& a_rz){m_x = a_rx; m_y = a_ry; m_z = a_rz;}
	void vSetPhiNegatif(const bool& a_rPhiNeg) {m_phiNegative = a_rPhiNeg;}

	double getR() const {return getNorm();}
	double getPhi() const {return acos(m_z/getNorm());}
	double getTheta() const {double a_theta = atan(m_y/m_x); if (m_x>0.0) return a_theta; else return (a_theta + M_PI);}

	void vCartesianToSpherical(double& a_rR, double& a_rPhi, double& a_rTheta) const;
	void vSphericalToCartesian(const double& a_rR, const double& a_rPhi, const double& a_rTheta);

private:
	
	double m_x;
	double m_y;
	double m_z;
	bool m_phiNegative;
};
#endif

// End of File
