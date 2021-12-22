#include "CMatrix.h"

CMatrix::CMatrix(float changeMatrixm[3][3])
{
	for (int y = 0; y < 3; y++)
	{
		for (int x = 0; x < 3; x++)
		{
			m_matrix[y][x] = changeMatrixm[y][x];
		}
	}
}

CMatrix::~CMatrix()
{

}

CMatrix CMatrix::operator+(CMatrix& changeMatrix)
{
	for (int y = 0; y < 3; y++)
	{
		for (int x = 0; x < 3; x++)
		{
			m_matrix[y][x] += changeMatrix.m_matrix[y][x];
		}
	}

	return CMatrix(m_matrix);
}

CMatrix CMatrix::operator-(CMatrix& changeMatrix)
{
	for (int y = 0; y < 3; y++)
	{
		for (int x = 0; x < 3; x++)
		{
			m_matrix[y][x] -= changeMatrix.m_matrix[y][x];
		}
	}

	return CMatrix(m_matrix);
}

CMatrix CMatrix::operator*(CMatrix& changeMatrix)
{
	// °ö¼À °á°ú°ª ÀúÀå
	float _temp[3][3] = { 0, };

	// °ö¼À ÇÕ
	int _sum = 0;

	// Çà·ÄÀÇ °ö¼À
	int column = 0;

	// Çà
	for (int row = 0; row < 3; row++)
	{
		for (int y = 0; y < 3; y++)
		{
			for (int x = 0; x < 3; x++)
			{
				_sum += m_matrix[row][x] * changeMatrix.m_matrix[x][y];
			}

			_temp[row][column] = _sum;
			_sum = 0;
			column++;
		}

		column = 0;
	}

	// °ö¼À°á°ú¸¦ Çà·Ä ¿ä¼Ò¿¡ ³Ö´Â´Ù
	for (int y = 0; y < 3; y++)
	{
		for (int x = 0; x < 3; x++)
		{
			m_matrix[y][x] = _temp[y][x];
		}
	}

	return CMatrix(m_matrix);
}