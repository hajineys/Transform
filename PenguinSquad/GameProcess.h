#pragma once

class GameObject;

class GameProcess
{
public:
	GameProcess();
	~GameProcess();

private:
	HWND m_hWnd;

	Direct2D* m_pD2DEngine;

	//�׽�Ʈ�� �ӽ� ������Ʈ
	GameObject* m_pPlayer;
	GameObject* m_pTarget;

public:
	// Register the window class and call methods for instantiating drawing resources
	bool Initialize(HINSTANCE hInstance);

	// Process and dispatch messages
	void MessageLoop();
	void GameLoop();

	// Key-Input
	void KeyInput(GameObject* pgameObject);
	
	// ���� ����� delete
	void Finalize();

private:
	// The windows procedure
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
};