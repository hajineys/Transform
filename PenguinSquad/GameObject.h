#pragma once

#include "CVector.h"

class Direct2D;

enum class ObjectType
{
	Circle,
	Rect,
	OBB
};

class GameObject
{
public:
	GameObject();
	~GameObject();

protected:
	// ��ü�� ��ǥ, pivot, ������
	CVector m_Pos;
	CVector m_CenterPos;
	float m_Size;

	// 4���� �������� ���� �⺻ CollisionBox
	CVector m_rect[4];

	// ��ü�� Ÿ��, �浹����
	ObjectType m_Type;
	bool m_IsCollided;

public:
	// Getter / Setter
	ObjectType GetType() const { return m_Type; }
	void SetType(ObjectType type) { m_Type = type; }
	float GetSize() const { return m_Size; }

	CVector GetPos() { return m_Pos; }

public:
	virtual void Initialize(int posX, int posY, float size);
	void Update();
	virtual void Draw(Direct2D* pD2DEngine);
	virtual void Finalize();

	// �浹üũ
	void CheckCollision(GameObject* pgameObject);

	void CircleCollision(GameObject* pgameObject);
	void AABBCollision(GameObject* pgameObject);
	void OBBCollision(GameObject* pgameObject);

	/// TRS
	void Translate(float dx, float dy);
	void Rotate(float angle);
	void Scale(float sx, float sy, float radius);
};