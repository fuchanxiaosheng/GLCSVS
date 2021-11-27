#include "RTWindow.h"

class RTWindow::WindowTemplate
{
public:
	static const char* GetName() noexcept
	{
		return wndTemplateName;
	}
	static HINSTANCE GetInstance() noexcept
	{
		return wndTemplate.hInst;
	}

private:
	WindowTemplate() noexcept
		: hInst(GetModuleHandle(nullptr))
	{
		WNDCLASSEX wc = { 0 };
		wc.cbSize = sizeof(wc);
		wc.style = CS_OWNDC;
		wc.lpfnWndProc = HandleMsgSetup;
		wc.cbClsExtra = 0;
		wc.cbWndExtra = 0;
		wc.hInstance = GetInstance();;
		wc.hIcon = nullptr;
		wc.hCursor = nullptr;
		wc.hbrBackground = nullptr;
		wc.lpszMenuName = nullptr;
		wc.lpszClassName = GetName();
		wc.hIconSm = nullptr;

		RegisterClassEx(&wc);
	}

	~WindowTemplate()
	{
		UnregisterClass(wndTemplateName, GetInstance());
	}
	WindowTemplate(const WindowTemplate&) = delete;
	WindowTemplate& operator=(const WindowTemplate&) = delete;
	static constexpr const char* wndTemplateName = "RTRender Window";
	static WindowTemplate wndTemplate;
	HINSTANCE hInst;

};
RTWindow::WindowTemplate RTWindow::WindowTemplate::wndTemplate;

RTWindow::RTWindow(int width, int height, const char* name) noexcept
{
	RECT wr;
	wr.left = 100;
	wr.right = width = wr.left;
	wr.top = 100;
	wr.bottom = height + wr.top;
	AdjustWindowRect(&wr, WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU, FALSE);

	hWnd = CreateWindow(
		WindowTemplate::GetName(), name,
		WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU,
		CW_USEDEFAULT, CW_USEDEFAULT, wr.right - wr.left, wr.bottom - wr.top,
		nullptr, nullptr, WindowTemplate::GetInstance(), this
	);

	ShowWindow(hWnd, SW_SHOWDEFAULT);
}

RTWindow::~RTWindow()
{
	DestroyWindow(hWnd);
}

LRESULT WINAPI RTWindow::HandleMsgSetup(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept
{
	if (msg == WM_NCCREATE)
	{
		const CREATESTRUCTW* const pCreate = reinterpret_cast<CREATESTRUCTW*>(lParam);
		RTWindow* const pWnd = static_cast<RTWindow*>(pCreate->lpCreateParams);
		SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pWnd));
		SetWindowLongPtr(hWnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(&RTWindow::HandleMsgThunk));
		return pWnd->HandleMsg(hWnd, msg, wParam, lParam);
	}
}