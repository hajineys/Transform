#pragma once

class CMatrix
{
public:
	CMatrix(float changeMatrix[3][3]);
	~CMatrix();

public:
	// 3x3 ����� ����� �����
	float m_matrix[3][3];

	// ��ĳ����� ��� ���� ���ϱ� ���� ������ �����ε�
	CMatrix operator+ (CMatrix& changeMatrix);
	CMatrix operator- (CMatrix& changeMatrix);
	CMatrix operator* (CMatrix& changeMatrix);
	
	//CMatrix operator+ (CMatrix& _m);
};