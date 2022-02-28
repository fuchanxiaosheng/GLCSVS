#pragma once
#include <Windows.h>

#include "RTKeyboard.h"
#include "RTMouse.h"

class RTWindow
{

public:
	RTWindow(int width, int height, const char* name) noexcept;
	~RTWindow();
	RTWindow(const RTWindow&) = delete;
	RTWindow& operator=(const RTWindow&) = delete;
	void SetTitle(const std::string& title);

private:
	static LRESULT CALLBACK HandleMsgSetup(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept;
	static LRESULT CALLBACK HandleMsgThunk(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept;
	LRESULT HandleMsg(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept;


public:
	RTKeyboard kbd;
	RTMouse mouse;

private:
	class WindowTemplate;
	int width;
	int height;
	HWND hWnd;
};
