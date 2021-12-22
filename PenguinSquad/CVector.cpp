#include "CVector.h"
#include "CMatrix.h"

CVector::CVector()
{

}

CVector::CVector(float curX, float curY)
	:x(curX), y(curY)
{
	
}

CVector::~CVector()
{

}

CVector CVector::operator*(CMatrix& changeMatrix)
{
	CVector _result(0,0);

	_result.x = changeMatrix.m_matrix[0][0] * x + changeMatrix.m_matrix[0][1] * y + changeMatrix.m_matrix[0][2] * 1;
	_result.y = changeMatrix.m_matrix[1][0] * x + changeMatrix.m_matrix[1][1] * y + changeMatrix.m_matrix[1][2] * 1;

	return _result;
}