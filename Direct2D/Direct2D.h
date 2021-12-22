#pragma once

#include <d2d1.h>
#pragma comment(lib, "d2d1.lib")
#include <d2d1helper.h>

// 2���� ���ͻ��
#include <dcommon.h>

#include <dwrite.h>
#pragma comment(lib, "dwrite.lib")

#include <stdio.h>

class Direct2D
{
public:
	Direct2D();
	~Direct2D();

private:
	// Render ����
	ID2D1Factory* m_pDirect2dFactory;
	ID2D1HwndRenderTarget* m_pRenderTarget;

	// Text ����
	IDWriteFactory* m_pDWriteFactory;
	IDWriteTextFormat* m_pTextFormat;

	// Brush ����
	ID2D1SolidColorBrush* m_pNowBrush;

public:
	// �ʱ�ȭ
	void Initialize(HWND hWnd);

	// Render
	void BeginRender();
	void EndRender();
	
	// Brush
	void SetBrushColor(float r, float g, float b, float a);

	// Draw
	void DrawLine(int x1, int y1, int x2, int y2);
	void DrawRectangle(int x1, int y1, int x2, int y2);
	void DrawEllipse(int x, int y, int size);

	// Text
	void DrawText(int x, int y, const WCHAR* pch, ...);

	// �ӽ�
	void SetTransform(D2D1_MATRIX_3X2_F TransFormMatrix);

	// �޸� ����
	void Finalize();
};