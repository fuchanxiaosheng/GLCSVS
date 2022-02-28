#include <Windows.h>
#include <sstream>

#include "spdlog/spdlog.h"

#include "Window/RTMessageMap.h"
#include "Window/RTWindow.h"

int main()
{
	RTWindow window(800, 500, "RTRender");

	MSG msg;
	BOOL gResult;
	while ((gResult = GetMessage(&msg, nullptr, 0, 0)) > 0)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
		/*if (window.kbd.KeyIsPressed(VK_SPACE))
		{
			spdlog::info("space key is pressed");
		}*/
		static int i = 0;
		while (!window.mouse.IsEmpty())
		{
			const auto e = window.mouse.Read();
			switch (e.GetType())
			{
			case RTMouse::Event::Type::Leave:
				spdlog::info("Gone");
				break;
			case RTMouse::Event::Type::Move:
				spdlog::info("mouse position: ({}, {})", e.GetPosX(), e.GetPosY());
				break;
			case RTMouse::Event::Type::WheelUp:
				i++;
				spdlog::info("Up:{}", i);
				break;
			case RTMouse::Event::Type::WheelDown:
				spdlog::info("Down:{}", i);
				break;
			}
		}

	}

	if (gResult == -1)
	{
		return -1;
	}
	
	return msg.wParam;
}