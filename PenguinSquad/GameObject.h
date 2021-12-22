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
	// 객체의 좌표, pivot, 반지름
	CVector m_Pos;
	CVector m_CenterPos;
	float m_Size;

	// 4개의 꼭짓점을 가진 기본 CollisionBox
	CVector m_rect[4];

	// 객체의 타입, 충돌유무
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

	// 충돌체크
	void CheckCollision(GameObject* pgameObject);

	void CircleCollision(GameObject* pgameObject);
	void AABBCollision(GameObject* pgameObject);
	void OBBCollision(GameObject* pgameObject);

	/// TRS
	void Translate(float dx, float dy);
	void Rotate(float angle);
	void Scale(float sx, float sy, float radius);
};