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
		while (!window.mouse.IsEmpty())
		{
			const auto e = window.mouse.Read();
			if (e.GetType() == RTMouse::Event::Type::Move)
			{
				spdlog::info("mouse position: ({}, {})", e.GetPosX(), e.GetPosY());
			}
		}
	}

	if (gResult == -1)
	{
		return -1;
	}
	
	return msg.wParam;
}