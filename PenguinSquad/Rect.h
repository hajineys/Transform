#pragma once

#include <d2d1.h>

#include "GameObject.h"

/// <summary>
/// GameObject를 부모로 상속받은 Rect Class
/// 
/// 2021. 01. 28. Hacgeum
/// </summary>
class Rect : public GameObject
{
public:
	Rect();
	~Rect();

public:
	virtual void Initialize(int posX, int posY, float size);
	virtual void Update();
	virtual void Draw(Direct2D* pD2DEngine);
	virtual void Finalize();
};