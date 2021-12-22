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
	// �浹������ ���� Brush ���� �ٸ��� �Ѵ�
	if (m_IsCollided == true)
	{
		// ���ǻ�
		pD2DEngine->SetBrushColor(1.0f, 0.0f, 0.0f, 1.0f);
	}
	else
	{
		// ������
		pD2DEngine->SetBrushColor(0.0f, 0.0f, 0.0f, 1.0f);
	}

	// �ܰ���
	pD2DEngine->DrawEllipse(m_CenterPos.x, m_CenterPos.y, m_Size);

	// ���� �߽ɼ�
	pD2DEngine->SetBrushColor(0.0f, 0.0f, 1.0f, 1.0f);
	pD2DEngine->DrawLine(m_CenterPos.x, m_CenterPos.y, m_rect[0].x, m_rect[0].y);
	pD2DEngine->DrawLine(m_CenterPos.x, m_CenterPos.y, m_rect[3].x, m_rect[3].y);

	// ���� �߽ɼ�
	pD2DEngine->SetBrushColor(0.0f, 1.0f, 0.0f, 1.0f);
	pD2DEngine->DrawLine(m_CenterPos.x, m_CenterPos.y, m_rect[1].x, m_rect[1].y);
	pD2DEngine->DrawLine(m_CenterPos.x, m_CenterPos.y, m_rect[2].x, m_rect[2].y);
}

void Circle::Finalize()
{

}