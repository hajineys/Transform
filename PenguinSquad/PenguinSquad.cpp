// PenguinSquad.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

#include "framework.h"
#include "PenguinSquad.h"
#include "GameProcess.h"

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    // 애플리케이션 초기화를 수행합니다:
    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_PENGUINSQUAD));

    // 게임 프로세스 생성(메모리 할당)
    GameProcess* pGameProcess = new GameProcess;

    if (!pGameProcess->Initialize(hInstance))
    {
        return FALSE;
    }

    pGameProcess->MessageLoop();
    pGameProcess->Finalize();

    return 0;
}