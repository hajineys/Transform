#include "framework.h"
#include "GameObject.h"
#include "CMatrix.h"

GameObject::GameObject()
	:m_Pos{ 0, 0 }, m_CenterPos{ 0, 0 }, m_Size(0), m_IsCollided(false)
{

}

GameObject::~GameObject()
{

}

void GameObject::Initialize(int posX, int posY, float size)
{
	// 위치 초기화
	m_Pos.x = posX;
	m_Pos.y = posY;

	// 사이즈 초기화
	m_Size = size;

	// Left, Top, Right, Bottom 꼭짓점에 파라미터 값을 이용하여 m_rect 초기화
	m_rect[0] = { (float)posX, (float)posY };
	m_rect[1] = { (float)posX + size, (float)posY };
	m_rect[2] = { (float)posX, (float)posY + size };
	m_rect[3] = { (float)posX + size, (float)posY + size };

	// 중점 초기화
	m_CenterPos = { (m_rect[0].x + m_rect[3].x) / 2, (m_rect[0].y + m_rect[3].y) / 2 };
}

void GameObject::Update()
{
	// 현재 내 위치에 따라 중점을 업데이트 해준다.
	m_CenterPos = { (m_rect[0].x + m_rect[3].x) / 2, (m_rect[0].y + m_rect[3].y) / 2 };
}

void GameObject::Draw(Direct2D* pD2DEngine)
{

}

void GameObject::Finalize()
{

}

void GameObject::CheckCollision(GameObject* pgameObject)
{
	if (pgameObject->m_Type == ObjectType::Circle)
	{
		CircleCollision(pgameObject);
	}

	else if (pgameObject->m_Type == ObjectType::Rect)
	{
		AABBCollision(pgameObject);
	}

	else if (pgameObject->m_Type == ObjectType::Rect)
	{
		OBBCollision(pgameObject);
	}
}

void GameObject::CircleCollision(GameObject* pgameObject)
{
	float R1 = pgameObject->m_Size;
	float R2 = m_Size;

	float baseline = pgameObject->m_CenterPos.x - m_CenterPos.x;
	float height = pgameObject->m_CenterPos.y - m_CenterPos.y;
	float hypotenuse = (baseline * baseline) + (height * height);
	float interval = sqrt(hypotenuse);

	if (pgameObject != nullptr)
	{
		// 충돌했다!
		if (interval <= (R1 + R2))
		{
			m_IsCollided = true;
			pgameObject->m_IsCollided = true;
		}
		// 아니다
		else
		{
			m_IsCollided = false;
			pgameObject->m_IsCollided = false;
		}
	}
}

void GameObject::AABBCollision(GameObject* pgameObject)
{
	if (pgameObject != nullptr)
	{
		// 충돌했다!
		if (pgameObject->m_rect[0].x <= m_rect[1].x &&
			m_rect[0].x <= pgameObject->m_rect[1].x &&
			pgameObject->m_rect[2].x <= m_rect[3].x &&
			m_rect[2].x <= pgameObject->m_rect[3].x &&
			pgameObject->m_rect[0].y <= m_rect[2].y &&
			m_rect[0].y <= pgameObject->m_rect[2].y &&
			pgameObject->m_rect[1].y <= m_rect[3].y &&
			m_rect[1].y <= pgameObject->m_rect[3].y)
		{
			m_IsCollided = true;
			pgameObject->m_IsCollided = true;
		}
		// 아니다
		else
		{
			m_IsCollided = false;
			pgameObject->m_IsCollided = false;
		}
	}
}

void GameObject::OBBCollision(GameObject* pgameObject)
{
	// 추가 구현 예정
}

void GameObject::Translate(float dx, float dy)
{
	// 이동행렬을 만들었다.
	float _translate[3][3] =
	{
		{1, 0, dx},
		{0, 1, dy},
		{0, 0,  1}
	};

	CMatrix _tranlateMatrix(_translate);

	// 자기 포지션 * 이동행렬 = 이동행렬만큼 이동함
	m_rect[0] = m_rect[0] * _tranlateMatrix;
	m_rect[1] = m_rect[1] * _tranlateMatrix;
	m_rect[2] = m_rect[2] * _tranlateMatrix;
	m_rect[3] = m_rect[3] * _tranlateMatrix;
}

void GameObject::Rotate(float angle)
{
	// 원점으로 이동
	Translate(-(m_CenterPos.x), -(m_CenterPos.y));

	const double pi = 3.14159265358979f;
	float radian = angle * pi / 180;

	// 회전행렬을 만들었다.
	float _rotate[3][3] =
	{
		{  cos(radian),  sin(radian), 0},
		{ -sin(radian),  cos(radian), 0},
		{            0,            0, 1}
	};

	CMatrix _rotateMatrix(_rotate);

	// 자기 포지션 * 회전행렬 = 회전행렬만큼 이동함
	m_rect[0] = m_rect[0] * _rotateMatrix;
	m_rect[1] = m_rect[1] * _rotateMatrix;
	m_rect[2] = m_rect[2] * _rotateMatrix;
	m_rect[3] = m_rect[3] * _rotateMatrix;

	Translate(m_CenterPos.x, m_CenterPos.y);
}

void GameObject::Scale(float sx, float sy, float radius)
{
	// 원점으로 이동
	Translate(-(m_CenterPos.x), -(m_CenterPos.y));

	float _scale[3][3] =
	{
		{sx,  0, 0},
		{ 0, sy, 0},
		{ 0,  0, 1}
	};

	CMatrix _scaleMatrix(_scale);

	// 자기 포지션 * 크기행렬 = 크기행렬만큼 변환함
	m_rect[0] = m_rect[0] * _scaleMatrix;
	m_rect[1] = m_rect[1] * _scaleMatrix;
	m_rect[2] = m_rect[2] * _scaleMatrix;
	m_rect[3] = m_rect[3] * _scaleMatrix;

	m_Size += radius;

	Translate(m_CenterPos.x, m_CenterPos.y);
}