#pragma once
#include <Windows.h>

class RTWindow
{

public:
	RTWindow(int width, int height, const char* name) noexcept;
	~RTWindow();
	RTWindow(const RTWindow&) = delete;
	RTWindow& operator=(const RTWindow&) = delete;

private:
	static LRESULT CALLBACK HandleMsgSetup(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept;
	static LRESULT CALLBACK HandleMsgThunk(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept;
	LRESULT HandleMsg(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept;

private:
	class WindowTemplate;
	int width;
	int height;
	HWND hWnd;
};
