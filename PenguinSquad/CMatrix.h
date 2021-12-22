#pragma once

class CMatrix
{
public:
	CMatrix(float changeMatrix[3][3]);
	~CMatrix();

public:
	// 3x3 모양의 행렬을 만든다
	float m_matrix[3][3];

	// 행렬끼리의 결과 값을 구하기 위한 연산자 오버로딩
	CMatrix operator+ (CMatrix& changeMatrix);
	CMatrix operator- (CMatrix& changeMatrix);
	CMatrix operator* (CMatrix& changeMatrix);
	
	//CMatrix operator+ (CMatrix& _m);
};