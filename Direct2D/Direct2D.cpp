// Direct2D.cpp : 정적 라이브러리를 위한 함수를 정의합니다.
//

#include "pch.h"
#include "Direct2D.h"

template<class Interface>
inline void SafeRelease(Interface** ppInterfaceToRelease)
{
	if (*ppInterfaceToRelease != NULL)
	{
		(*ppInterfaceToRelease)->Release();
		(*ppInterfaceToRelease) = NULL;
	}
}

Direct2D::Direct2D()
	:m_pDirect2dFactory(nullptr),
	m_pRenderTarget(nullptr),
	m_pDWriteFactory(nullptr),
	m_pTextFormat(nullptr),
	m_pNowBrush(nullptr)
{

}

Direct2D::~Direct2D()
{

}

void Direct2D::Initialize(HWND hWnd)
{
	// 컴포넌트를 사용할 수 있도록 프로그램을 초기화한다.
	HRESULT hr = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED);

	if (SUCCEEDED(hr))
	{
		// Create a Direct2D factory
		hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &m_pDirect2dFactory);
	}

	if (SUCCEEDED(hr))
	{
		RECT rc;
		GetClientRect(hWnd, &rc);

		// 화면의 사이즈
		D2D1_SIZE_U size = D2D1::SizeU(
			rc.right - rc.left,
			rc.bottom - rc.top);

		// Create a Direct2D render target
		hr = m_pDirect2dFactory->CreateHwndRenderTarget(
			D2D1::RenderTargetProperties(),
			D2D1::HwndRenderTargetProperties(hWnd, D2D1::SizeU(rc.right - rc.left, rc.bottom - rc.top)),
			&m_pRenderTarget);

		// Create a Basic Brush
		m_pRenderTarget->CreateSolidColorBrush(
			D2D1::ColorF(D2D1::ColorF::Black),
			&m_pNowBrush);
	}

	if (SUCCEEDED(hr))
	{
		hr = DWriteCreateFactory(
			DWRITE_FACTORY_TYPE_SHARED,
			__uuidof(m_pDWriteFactory),
			reinterpret_cast<IUnknown**>(&m_pDWriteFactory));
	}

	static const WCHAR msc_fontName[] = L"굴림";
	static const FLOAT msc_fontSize = 20;

	if (SUCCEEDED(hr))
	{
		hr = m_pDWriteFactory->CreateTextFormat(
			msc_fontName,
			NULL,
			DWRITE_FONT_WEIGHT_NORMAL,
			DWRITE_FONT_STYLE_NORMAL,
			DWRITE_FONT_STRETCH_NORMAL,
			msc_fontSize,
			L"", //locale
			&m_pTextFormat);
	}

	// 텍스트 정렬 방식
	if (SUCCEEDED(hr))
	{
		// Left-Top the text horizontally and vertically.
		m_pTextFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_LEADING);
		m_pTextFormat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_NEAR);
	}
}

void Direct2D::BeginRender()
{
	// WM_PAINT BeginPaint와 비슷한 기능, 그릴 준비를 시작한다
	m_pRenderTarget->BeginDraw();

	// 더블버퍼링, 화면을 지운다(리셋)
	m_pRenderTarget->Clear(D2D1::ColorF(D2D1::ColorF::BlueViolet));
}

void Direct2D::EndRender()
{
	// WM_PAINT EndPaint와 비슷한 기능, 그리기를 마친다
	m_pRenderTarget->EndDraw();
}

void Direct2D::SetBrushColor(float r, float g, float b, float a)
{
	SafeRelease(&m_pNowBrush);

	m_pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF(r, g, b, a)), &m_pNowBrush);
}

void Direct2D::DrawLine(int x1, int y1, int x2, int y2)
{
	D2D1_POINT_2F startPoint = { x1, y1 };
	D2D1_POINT_2F endPoint = { x2, y2 };

	m_pRenderTarget->DrawLine(startPoint, endPoint, m_pNowBrush);
}

void Direct2D::DrawRectangle(int left, int top, int right, int bottom)
{
	D2D1_RECT_F rect = { left, top, right, bottom };

	m_pRenderTarget->DrawRectangle(rect, m_pNowBrush);
}

void Direct2D::DrawEllipse(int x, int y, int radius)
{
	D2D1_ELLIPSE ellipse;

	ellipse.point = { (float)x, (float)y };
	ellipse.radiusX = radius;
	ellipse.radiusY = radius;

	m_pRenderTarget->DrawEllipse(ellipse, m_pNowBrush);
}

void Direct2D::DrawText(int x, int y, const WCHAR* pch, ...)
{
	// 포맷 스트링 관련 버퍼, 가변인자 처리
	va_list ap;			// 현재 읽고 있는 번지를 기억
	va_start(ap, pch);	// ap 포인터 변수가 첫번째 가변인수를 가리키도록 초기화

	int len = _vscwprintf(pch, ap) + 1;
	WCHAR* buffer = new WCHAR[len];

	vswprintf_s(buffer, len, pch, ap);
	va_end(ap);

	int nLen = lstrlen(buffer);

	// 폰트별 차지하는 영역 계산 필요
	m_pRenderTarget->DrawText(buffer, wcslen(buffer), m_pTextFormat,
		D2D1::RectF((float)x, (float)y, (float)(x + 500), (float)(y + 40)),
		m_pNowBrush);

	// 포맷관련 버퍼 삭제
	delete[] buffer;
}

void Direct2D::SetTransform(D2D1_MATRIX_3X2_F TransFormMatrix)
{
	// Direct2D 헬퍼 함수를 통한 Transform
	m_pRenderTarget->SetTransform(TransFormMatrix);
}

void Direct2D::Finalize()
{
	// delete
	SafeRelease(&m_pDirect2dFactory);
	SafeRelease(&m_pRenderTarget);
	SafeRelease(&m_pDWriteFactory);
	SafeRelease(&m_pTextFormat);
	SafeRelease(&m_pNowBrush);
}