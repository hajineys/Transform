#pragma once

#include "GameObject.h"

/// <summary>
/// GameObject를 부모로 상속받은 Circle Class
/// 
/// 2021. 01. 28. Hacgeum
/// </summary>
class Circle : public GameObject
{
public:
	Circle();
	~Circle();

public:
	virtual void Initialize(int posX, int posY, float size);
	virtual void Update();
	virtual void Draw(Direct2D* pD2DEngine);
	virtual void Finalize();
};