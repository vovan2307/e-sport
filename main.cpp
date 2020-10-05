#import "C:\Windows\SysWOW64\Macromed\Flash\FlashUtil32_32_0_0_433_Plugin.dll" rename_namespace("Flash")
#pragma comment(lib, "atl")
#include  <atlbase.h>
CComModule _Module;
#include <atlwin.h>
#include <windows.h>
#include <string.h>

HINSTANCE g_hInst;


LRESULT CALLBACK WndProc(HWND hWnd, UINT uMessage, WPARAM wParam, LPARAM lParam)
{
	static Flash::FlashBrokerImp* m_pFlash;
	static HWND hWndActiveX;
	switch (uMessage)
	{
	case WM_CREATE:
	{
		WCHAR wcPath[MAX_PATH];
		RECT rc; GetClientRect(hWnd, &rc);
		hWndActiveX = CreateWindowEx(0, L"AtlAxWin", NULL, WS_CHILD | WS_VISIBLE,
			0, 0, rc.right, rc.bottom, hWnd, NULL, g_hInst, NULL);
		if (FAILED(CoCreateInstance(__uuidof(Flash::ShockwaveFlash), NULL, CLSCTX_ALL,
			__uuidof(Flash::IShockwaveFlash), (void**)&m_pFlash)))
			return -1;
		if (FAILED(AtlAxAttachControl(m_pFlash, hWndActiveX, NULL))){
			m_pFlash->Release();
			return -1;
		}
		GetCurrentDirectoryW(MAX_PATH, wcPath);
		wcscat(wcPath, L"\\shapes.swf");
		HRESULT hres = m_pFlash->LoadMovie(0, wcPath);
		m_pFlash->Menu = VARIANT_FALSE;
	}
	return 0;

	case WM_SIZE:
		MoveWindow(hWndActiveX, 0, 0, LOWORD(lParam), HIWORD(lParam), TRUE);
		return 0;

	case WM_PAINT:
	case WM_ERASEBKGND:
		ValidateRect(hWnd, NULL);
		return 0;

	case WM_DESTROY:
		DestroyWindow(hWndActiveX);
		m_pFlash->Release();
		PostQuitMessage(0);
		return 0;
	}

	return DefWindowProc(hWnd, uMessage, wParam, lParam);
}

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrev, LPSTR lpCmdLine, int nCmdShow)
{
	CoInitialize(NULL);
	AtlAxWinInit();
	g_hInst = hInstance;

	WNDCLASSEX wcex = {
		sizeof(WNDCLASSEX), 0, WndProc, 0, 0, g_hInst, LoadIcon(NULL, IDI_APPLICATION),
		LoadCursor(NULL, IDC_ARROW), (HBRUSH)(COLOR_WINDOW + 1), NULL, L"SWFWin", NULL,
	};
	if (!RegisterClassEx(&wcex))
		return MessageBox(HWND_DESKTOP, L"Could not register class!", L"Error", MB_ICONERROR | MB_OK);

	int nX = ((GetSystemMetrics(SM_CXSCREEN) - 400) / 2),
		nY = ((GetSystemMetrics(SM_CYSCREEN) - 340) / 2);
	HWND hWnd = CreateWindowEx(0, wcex.lpszClassName, L"SWF In Window Example - by Napalm",
		WS_OVERLAPPEDWINDOW, nX, nY, 400, 340, HWND_DESKTOP, NULL, g_hInst, NULL);
	if (!hWnd)
		return MessageBox(HWND_DESKTOP, L"Could not create window!", L"Error", MB_ICONERROR | MB_OK);

	ShowWindow(hWnd, nCmdShow);

	MSG Msg;
	while (GetMessage(&Msg, NULL, 0, 0)){
		TranslateMessage(&Msg);
		DispatchMessage(&Msg);
	}

	CoUninitialize();
	return (int)Msg.wParam;
}