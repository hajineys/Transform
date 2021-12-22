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

	//테스트용 임시 오브젝트
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
	
	// 게임 종료시 delete
	void Finalize();

private:
	// The windows procedure
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
};