#include <Windows.h>
#include <sstream>

#include "spdlog/spdlog.h"

#include "Window/RTMessageMap.h"

//void DrawBitmap(HWND hwnd, int x, int y, int nBmpWidth, int nBmpHeight, const unsigned char* pBmpData)
//{
//	HBITMAP hBitmap = ::CreateBitmap(nBmpWidth, nBmpHeight, 1, 32, pBmpData);
//	HDC hWndDc = ::GetDC(hwnd);
//	HDC hMemDc = ::CreateCompatibleDC(hWndDc);
//	HBITMAP hOldBitmap = (HBITMAP)::SelectObject(hMemDc, hBitmap);
//	::BitBlt(hWndDc, x, y, nBmpWidth, nBmpHeight, hMemDc, 0, 0, SRCCOPY);
//	::SelectObject(hMemDc, hOldBitmap);
//	::DeleteObject(hBitmap);
//	::DeleteDC(hMemDc);
//	::ReleaseDC(hwnd, hWndDc);
//}

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	static WindowsMessageMap mm;
	spdlog::info(mm(msg, lParam, wParam).c_str());

	switch (msg)
	{
	case WM_CLOSE:
		PostQuitMessage(69);
		break;
	case WM_KEYDOWN:
		if (wParam == 'D')
		{
			SetWindowText(hWnd, "Respects");
		}
		break;
	case WM_KEYUP:
		if (wParam == 'F')
		{
			SetWindowText(hWnd, "Dangerfield");
		}
		break;
	case WM_CHAR:
	{
		static std::string title;
		title.push_back((char)wParam);
		SetWindowText(hWnd, title.c_str());
		break;
	}
	case WM_LBUTTONDOWN:
	{
		const POINTS pt = MAKEPOINTS(lParam);
		std::ostringstream oss;
		oss << "(" << pt.x << "," << pt.y << ")";
		SetWindowText(hWnd, oss.str().c_str());
		break;
	}
	}

	return DefWindowProc(hWnd, msg, wParam, lParam);
}

int main()
{
	const auto pClassName = "RTRender";
	HINSTANCE hInstance = GetModuleHandle(nullptr);

	WNDCLASSEX wc = { 0 };
	wc.cbSize = sizeof(wc);
	wc.style = CS_OWNDC;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = nullptr;
	wc.hCursor = nullptr;
	wc.hbrBackground = nullptr;
	wc.lpszMenuName = nullptr;
	wc.lpszClassName = pClassName;
	wc.hIconSm = nullptr;

	RegisterClassEx(&wc);
	
	spdlog::info("register window class");

	HWND hWnd = CreateWindowEx(
		0, pClassName, "RTRender",
		WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU,
		200, 200, 640, 480,
		nullptr, nullptr, hInstance, nullptr);
	spdlog::info("acquire the window instance");
	if (hWnd == nullptr)
		spdlog::error("acquire window instance failed");

	ShowWindow(hWnd, SW_SHOW);
	spdlog::info("show window");

	MSG msg;
	BOOL gResult;
	while ((gResult = GetMessage(&msg, nullptr, 0, 0)) > 0)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	if (gResult == -1)
	{
		return -1;
	}
	else
	{
		return msg.wParam;
	}

	return 0;
}