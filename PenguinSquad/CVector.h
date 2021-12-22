#pragma once

#include "CMatrix.h"

class CVector
{
public:
	CVector();
	CVector(float curX, float curY);
	~CVector();

public:
	float x;
	float y;

	// ���ͳ����� ��� ���� ���ϱ� ���� ������ �����ε�
	CVector operator+ (CVector& vector) { x += vector.x; y += vector.y; return CVector(x, y); }
	CVector operator- (CVector& vector) { x -= vector.x; y -= vector.y; return CVector(x, y); }
	CVector operator* (CVector& vector) { x *= vector.x; y *= vector.y; return CVector(x, y); }
	CVector operator/ (CVector& vector) { x /= vector.x; y /= vector.y; return CVector(x, y); }

	CVector operator* (CMatrix& changeMatrix);
};