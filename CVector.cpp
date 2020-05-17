#include "CVector.h"
#include "Point3D.h"
#include "Macros.h"

//============================<CVector::CVector>===============================
//
// Summary:  Constructor with x, y and z values
//          
//=============================================================================
CVector::CVector(double a_x, double a_y, double a_z)
:m_x(a_x), m_y(a_y),m_z(a_z)
{
}

//============================<CVector::CVector>===============================
//
// Summary:  Constructor with two points, the start and end of the vector
//          
//=============================================================================
CVector::CVector(const Point3D & a_rStart, const Point3D & a_rEnd)
{
	m_x = a_rEnd.getX() - a_rStart.getX();
	m_y = a_rEnd.getY() - a_rStart.getY();
	m_z = a_rEnd.getZ() - a_rStart.getZ();
}

//=============================<CVector::getNorm>==============================
//
// Summary:  get the norm of the vector
//          
// Return Value: Double the value of the norm
//
//=============================================================================
double CVector::getNorm() const
{
	return sqrt( m_x * m_x + m_y * m_y + m_z * m_z );
}

//==========================<CVector::dotProduct>==============================
//
// Summary:  calculates the dot product with the b vector
//          
// Return Value: Double the value calculated
//
//=============================================================================
double CVector::dotProduct(const CVector& a_rB)
{
	return (m_x * a_rB.m_x + m_y * a_rB.m_y + m_z * a_rB.m_z);
}

//===========================<CVector::operator=>==============================
//
// Summary:  Copy constructor
//          
// Return Value: CVector
//
//=============================================================================
const CVector & CVector::operator = (const CVector & a_rRight)
{
	m_x = a_rRight.m_x;
	m_y = a_rRight.m_y;
	m_z = a_rRight.m_z;

	return *this;
}

//=============================<CVector::getEnd>===============================
//
// Summary:  Get the end point of the vector
//          
// Return Value: Point3D the end point of the vector
//
//=============================================================================
Point3D CVector::getEnd(const Point3D& a_rStart) const
{
	Point3D end;

	end.vSetX(m_x + a_rStart.getX());
	end.vSetY(m_y + a_rStart.getY());
	end.vSetZ(m_z + a_rStart.getZ());

	return end;
}

//===========================<CVector::operator+>==============================
//
// Summary:  + operator to add two vectors
//          
// Return Value: CVector the value calculated
//
//=============================================================================
CVector CVector::operator+(const CVector& a_rRight) const
{
	CVector vec;

	vec.m_x = m_x + a_rRight.m_x;
	vec.m_y = m_y + a_rRight.m_y;
	vec.m_z = m_z + a_rRight.m_z;

	return vec;
}

//========================<CVector::operator->===========================
//
// Summary:  - operator to subtract two vectors
//          
// Return Value: CVector the value calculated
//
//=============================================================================
CVector CVector::operator-(const CVector& a_rRight) const
{
	CVector vec;

   vec.m_x = m_x - a_rRight.m_x;
   vec.m_y = m_y - a_rRight.m_y;
   vec.m_z = m_z - a_rRight.m_z;

	return vec;
}

//==========================<CVector::operator*>===============================
//
// Summary:  * operator to multiplie two vectors
//          
// Return Value: CVector the value calculated
//
//=============================================================================
CVector CVector::operator*(const double a_value) const
{
	CVector vec;

   vec.m_x = m_x * a_value;
   vec.m_y = m_y * a_value;
   vec.m_z = m_z * a_value;

	return vec;
}

//===========================<CVector::crossProduct>===========================
//
// Summary:  Calculates the cross product with the a_rB vector
//          
// Return Value: CVector the result of the cross product
//
//=============================================================================
CVector CVector::crossProduct(const CVector& a_rB) const
{
	CVector vec;

	vec.m_x =   m_y * a_rB.m_z - a_rB.m_y * m_z;
	vec.m_y = -(m_x * a_rB.m_z - a_rB.m_x * m_z);
	vec.m_z =   m_x * a_rB.m_y - a_rB.m_x * m_y;

	return vec;
}

//===========================<CVector::normalize>==============================
//
// Summary:  Normalize the vector
//          
// Return Value: bool : true => the operation was done, the vector is not null
//
//=============================================================================
bool CVector::normalize()
{
	double norm = getNorm();
	if (norm!=0)
		*this = *this / norm;
	return (norm!=0);
}

//========================<CVector::vCartesianToSpherical>=====================
//
// Summary:  Calculates the spherical coordinates of the vector from 
//           the cartesian coordinates
//          
// Return Value: none
//
//=============================================================================
void CVector::vCartesianToSpherical(double& a_rR, double& a_rPhi, double& a_rTheta) const
{
	a_rR = getNorm();
	a_rPhi = acos(m_z / a_rR);

	if (m_x != 0)
		a_rTheta = atan(m_y/m_x);
	else
		a_rTheta = 0.0;

        if (m_x < 0.0)
		a_rTheta = a_rTheta + M_PI;

	a_rPhi   = RAD_TO_DEG(a_rPhi);
	a_rTheta = RAD_TO_DEG(a_rTheta);
}

//====================<CVector::vSphericalVersCartesian>======================
//
// Summary:  Calculates the cartesian coordinates of the vector from 
//           the spherical coordinates
//          
// Return Value: none
//
//=============================================================================
void CVector::vSphericalToCartesian(const double& a_rR, const double& a_rPhi, const double& a_rTheta)
{
	double phi   = DEG_TO_RAD(a_rPhi);
	double theta = DEG_TO_RAD(a_rTheta);

	m_x = a_rR * sin(phi) * cos(theta);
	m_y = a_rR * sin(phi) * sin(theta);
	m_z = a_rR * cos(phi);
}

//=============================<CVector::operator/>============================
//
// Summary:  / operator to divide a vector by a scalar
//          
// Return Value: none
//
//=============================================================================
CVector CVector::operator/(const double a_value) const
{
	CVector vec(*this);

	if (a_value != 0)
		vec = *this * (1/a_value);

	return vec;
}

//==========================<CVector::operator+=>==============================
//
// Summary:  += operator
//           adds the right vector to this one
//          
// Return Value: none
//
//=============================================================================
void CVector::operator+=(const CVector& a_rRight)
{
	m_x += a_rRight.getX();
	m_y += a_rRight.getY();
	m_z += a_rRight.getZ();
}

// End of File
