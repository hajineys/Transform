#include "framework.h"
#include "Circle.h"
#include "Direct2D.h"

Circle::Circle()
{

}

Circle::~Circle()
{

}

void Circle::Initialize(int posX, int posY, float size)
{
	GameObject::Initialize(posX, posY, size);

	m_Type = ObjectType::Circle;
}

void Circle::Update()
{

}

void Circle::Draw(Direct2D* pD2DEngine)
{
	// 충돌유무에 따라 Brush 색을 다르게 한다
	if (m_IsCollided == true)
	{
		// 뻘건색
		pD2DEngine->SetBrushColor(1.0f, 0.0f, 0.0f, 1.0f);
	}
	else
	{
		// 검은색
		pD2DEngine->SetBrushColor(0.0f, 0.0f, 0.0f, 1.0f);
	}

	// 외각선
	pD2DEngine->DrawEllipse(m_CenterPos.x, m_CenterPos.y, m_Size);

	// 가로 중심선
	pD2DEngine->SetBrushColor(0.0f, 0.0f, 1.0f, 1.0f);
	pD2DEngine->DrawLine(m_CenterPos.x, m_CenterPos.y, m_rect[0].x, m_rect[0].y);
	pD2DEngine->DrawLine(m_CenterPos.x, m_CenterPos.y, m_rect[3].x, m_rect[3].y);

	// 세로 중심선
	pD2DEngine->SetBrushColor(0.0f, 1.0f, 0.0f, 1.0f);
	pD2DEngine->DrawLine(m_CenterPos.x, m_CenterPos.y, m_rect[1].x, m_rect[1].y);
	pD2DEngine->DrawLine(m_CenterPos.x, m_CenterPos.y, m_rect[2].x, m_rect[2].y);
}

void Circle::Finalize()
{

}