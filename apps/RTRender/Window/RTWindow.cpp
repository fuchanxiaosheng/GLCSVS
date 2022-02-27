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
		wc.hInstance = GetInstance();
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
	wr.right = width + wr.left;
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

LRESULT CALLBACK RTWindow::HandleMsgSetup(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept
{
	if (msg == WM_NCCREATE)
	{
		const CREATESTRUCTW* const pCreate = reinterpret_cast<CREATESTRUCTW*>(lParam);
		RTWindow* const pWnd = static_cast<RTWindow*>(pCreate->lpCreateParams);
		SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pWnd));
		SetWindowLongPtr(hWnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(&RTWindow::HandleMsgThunk));
		return pWnd->HandleMsg(hWnd, msg, wParam, lParam);
	}

	return DefWindowProc(hWnd, msg, wParam, lParam);
}

LRESULT CALLBACK RTWindow::HandleMsgThunk(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept
{
	RTWindow* const pWnd = reinterpret_cast<RTWindow*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));
	return pWnd->HandleMsg(hWnd, msg, wParam, lParam);
}

LRESULT RTWindow::HandleMsg(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept
{
	switch (msg)
	{
	case WM_CLOSE:
		PostQuitMessage(0);
		return 0;
	case WM_KILLFOCUS:
		kbd.ClearState();
		break;

	case WM_KEYDOWN:
		if (!(lParam & 0x40000000) || kbd.AutorepeatIsEnabled())
		{
			kbd.OnKeyPressed(static_cast<unsigned char>(wParam));
		}
		break;
	case WM_KEYUP:
	case WM_SYSKEYUP:
		kbd.OnKeyPressed(static_cast<unsigned char>(wParam));
		break;
	case WM_CHAR:
		kbd.OnChar(static_cast<unsigned char>(wParam));
		break;

	case WM_MOUSEMOVE:
	{
		POINTS pt = MAKEPOINTS(lParam);
		mouse.OnMouseMove(pt.x, pt.y);
	}
	case WM_LBUTTONDOWN:
	{
		POINTS pt = MAKEPOINTS(lParam);
		mouse.OnLeftPressed(pt.x, pt.y);
		break;
	}
	case WM_RBUTTONUP:
	{
		const POINTS pt = MAKEPOINTS(lParam);
		mouse.OnRightPressed(pt.x, pt.y);
		break;
	}
	case WM_MOUSEWHEEL:
	{
		const POINTS pt = MAKEPOINTS(lParam);
		if (GET_WHEEL_DELTA_WPARAM(wParam) > 0)
		{
			mouse.OnWheelUp(pt.x, pt.y);
		}
		else if (GET_WHEEL_DELTA_WPARAM(wParam) < 0)
		{
			mouse.OnWheelDown(pt.x, pt.y);
		}
		break;
	}
	}

	return DefWindowProc(hWnd, msg, wParam, lParam);
}