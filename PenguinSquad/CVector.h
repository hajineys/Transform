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

	// 벡터끼리의 결과 값을 구하기 위한 연산자 오버로딩
	CVector operator+ (CVector& vector) { x += vector.x; y += vector.y; return CVector(x, y); }
	CVector operator- (CVector& vector) { x -= vector.x; y -= vector.y; return CVector(x, y); }
	CVector operator* (CVector& vector) { x *= vector.x; y *= vector.y; return CVector(x, y); }
	CVector operator/ (CVector& vector) { x /= vector.x; y /= vector.y; return CVector(x, y); }

	CVector operator* (CMatrix& changeMatrix);
};