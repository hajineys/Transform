#include "framework.h"
#include "GameProcess.h"
#include "Direct2D.h"
#include "GameObject.h"
#include "Circle.h"
#include "Rect.h"

GameProcess::GameProcess()
	:m_hWnd(nullptr), m_pD2DEngine(nullptr)
{

}

GameProcess::~GameProcess()
{

}

bool GameProcess::Initialize(HINSTANCE hInstance)
{
	// ���� ǥ���� �ؽ�Ʈ�Դϴ�
	WCHAR szTitle[] = L"bangbangbang";

	// Resister the window class
	WNDCLASSEX wcex = { sizeof(WNDCLASSEX) };
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = GameProcess::WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hbrBackground = NULL;
	wcex.lpszMenuName = NULL;
	wcex.hCursor = LoadCursor(NULL, IDI_APPLICATION);
	wcex.lpszClassName = szTitle;

	RegisterClassEx(&wcex);

	// Create the window
	m_hWnd = CreateWindowW(szTitle, szTitle, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

	if (!m_hWnd)
	{
		return FALSE;
	}

	ShowWindow(m_hWnd, SW_SHOWNORMAL);
	UpdateWindow(m_hWnd);

	// Direct2D Engine ����
	m_pD2DEngine = new Direct2D;

	// Direct2D Engine �ʱ�ȭ
	m_pD2DEngine->Initialize(m_hWnd);

	m_pPlayer = new Rect();
	m_pPlayer->Initialize(200, 200, 50);

	m_pTarget = new Rect();
	m_pTarget->Initialize(500, 200, 50);
}

void GameProcess::MessageLoop()
{
	MSG msg;

	while (true)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
			{
				break;
			}

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			// Ű �Է�
			KeyInput(m_pPlayer);

			// Object Update
			m_pPlayer->Update();
			m_pPlayer->CheckCollision(m_pTarget);

			m_pD2DEngine->BeginRender();

			m_pPlayer->Draw(m_pD2DEngine);
			m_pTarget->Draw(m_pD2DEngine);

			// Key Info
			m_pD2DEngine->SetBrushColor(0.0f, 0.0f, 0.0f, 1.0f);
			m_pD2DEngine->DrawText(50, 30, L"�̵� : ����Ű");
			m_pD2DEngine->DrawText(50, 55, L"ȸ�� : Q E(Circle ��������)");
			m_pD2DEngine->DrawText(50, 80, L"������ : R W(Circle ��������)");
			m_pD2DEngine->DrawText(50, 105, L"Circle / Box ����ȯ : Space Bar");
			m_pD2DEngine->DrawText(50, 130, L"CC, AABB ���� / OBB ���� �ȵ�(�߰� ���� ����)");

			m_pD2DEngine->EndRender();
		}
	}
}

void GameProcess::GameLoop()
{

}

void GameProcess::KeyInput(GameObject* pgameObject)
{
	if (GetAsyncKeyState(VK_UP) & 0x8000)
	{
		// ���� �̵�
		m_pPlayer->Translate(0, -10);
	}

	if (GetAsyncKeyState(VK_DOWN) & 0x8000)
	{
		// �Ʒ��� �̵�
		m_pPlayer->Translate(0, 10);
	}

	if (GetAsyncKeyState(VK_LEFT) & 0x8000)
	{
		// ���� �̵�
		m_pPlayer->Translate(-10, 0);
	}

	if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
	{
		// ������ �̵�
		m_pPlayer->Translate(10, 0);
	}

	if (GetAsyncKeyState(0x51) & 0x8000)
	{
		// Q 
		m_pPlayer->Rotate(5);
	}

	if (GetAsyncKeyState(0x45) & 0x8000)
	{
		// E 
		m_pPlayer->Rotate(-5);
	}

	if (GetAsyncKeyState(0x52) & 0x8000)
	{
		// R
		m_pPlayer->Scale(1.2f, 1.2f, 1.2f);
	}

	if (GetAsyncKeyState(0x57) & 0x8000)
	{
		// W
		m_pPlayer->Scale(0.9f, 0.9f, -0.9f);
	}

	if (GetAsyncKeyState(VK_SPACE) & 0x0001)
	{
		if (pgameObject->GetType() == ObjectType::Circle)
		{
			GameObject* _newPlayer = new Rect();
			_newPlayer->Initialize(m_pPlayer->GetPos().x, m_pPlayer->GetPos().y, m_pPlayer->GetSize());
			GameObject* _newTarget = new Rect();
			_newTarget->Initialize(m_pTarget->GetPos().x, m_pTarget->GetPos().y, m_pTarget->GetSize());

			delete m_pPlayer;
			delete m_pTarget;

			m_pPlayer = _newPlayer;
			m_pTarget = _newTarget;
		}
		else if (pgameObject->GetType() == ObjectType::Rect)
		{
			GameObject* _newPlayer = new Circle;
			_newPlayer->Initialize(m_pPlayer->GetPos().x, m_pPlayer->GetPos().y, m_pPlayer->GetSize());
			GameObject* _newTarget = new Circle;
			_newTarget->Initialize(m_pTarget->GetPos().x, m_pTarget->GetPos().y, m_pTarget->GetSize());

			delete m_pPlayer;
			delete m_pTarget;

			m_pPlayer = _newPlayer;
			m_pTarget = _newTarget;
		}
	}
}

void GameProcess::Finalize()
{
	// Direct2D ��� �� ����
	m_pD2DEngine->Finalize();
	delete m_pD2DEngine;
}

LRESULT CALLBACK GameProcess::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
	}

	return 0;
}